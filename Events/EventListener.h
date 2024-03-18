#pragma once

#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include "GameData.h"
#include "Binder.h"

class EventListener {
public:
    const int id;
    const int parent;

    EventListener() : parentData(nullptr), data(), id(0), parent(0), binder(nullptr), frozen(false) {};
    EventListener(const int newId, const int parent, const GameData *pData, Binder *binder) : parentData(pData), data(), id(newId), parent(parent), binder(binder), frozen(false) {};

    int getId() const { return id; }
    std::map<BindedData, int> getBinded() const { return binded; }

    void update(const GameData &delta) {
        data.update(delta);
    }

    void freeze() {
        frozen = true;
        for (auto it = binded.begin(); it != binded.end(); it++) {
            (*binder).stop(it->first);
        }
    }

    void unfreeze() {
        if (!frozen) return;
        for (auto it = binded.begin(); it != binded.end(); it++) {
            (*binder).bind(it->second, it->first);
        }
        redraw();
    }
protected:
    GameData data;
    const GameData *parentData;
    virtual void redraw() {}

    template<typename C, typename Callable, typename... Args>
    void bind(int c, Callable func, C listener, std::string label, Args &&... args) {
        BindedData wrapped = BindedData::wrap(listener, func, label, args...);
        if (c == -1) {
            (*binder).bind_no_charachter(wrapped);
        } else { 
            (*binder).bind(c, wrapped);
        }
        if (binded.find(wrapped) == binded.end()) {
            binded[wrapped] = c;
        } else {
            throw std::invalid_argument("Function already binded");
        }
    }

    template<typename C, typename Callable, typename... Args>
    void unbind(Callable func, C listener, std::string label, Args &&... args) {
        BindedData wrapped = BindedData::wrap(listener, func, label, args...);
        if (binded.find(wrapped) == binded.end()) {
            throw std::invalid_argument("Function not binded");
        }
        binded.erase(wrapped);
        (*binder).stop(wrapped);
    }
private:
    Binder *binder;
    std::map<BindedData, int> binded;
    bool frozen;
};