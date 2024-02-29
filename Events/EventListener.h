#pragma once

#include <string>
#include <memory>
#include <map>
#include "GameData.h"
#include "Binder.h"

class EventListener {
public:
    const int id;
    const int parent;

    EventListener() : parentData(nullptr), data(), id(0), parent(0), binder(nullptr) {};
    EventListener(const int newId, const int parent, const GameData *data, const Binder *binder) : parentData(data), data(), id(newId), parent(parent), binder(binder) {};

    int getId() const { return id; }

    void update(const GameData &delta) {
        data.update(delta);
    }

    void freeze() {
        for (auto it = binded.begin(); it != binded.end(); it++) {
            //(*binder).unbind(it->first, this, it->second);
        }
    }

    void unfreeze() {
        for (auto it = binded.begin(); it != binded.end(); it++) {
            //(*binder).bind(it->first, this, it->second);
        }
        //also redraw
    }
private:
    GameData data;
    const GameData *parentData;
    const Binder *binder;

    std::map<std::function<Message()>*, char> binded;
    
    void bind(std::function<Message()> *func, char c) {
        binded[func] = c;
        //(*binder).bind(func, this, c);
    }

    void unbind(std::function<Message()> *func) {
        binded.erase(func);
        //(*binder).unbind(func, this, c);
    }
};