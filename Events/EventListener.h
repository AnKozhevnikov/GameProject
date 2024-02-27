#pragma once

#include <string>
#include <memory>
#include "GameData.h"
#include "Binder.h"

class EventListener {
public:
    EventListener(const GameData &newData, const int newId, const Binder &newBinder) : data(newData), id(newId), binder(binder) {};
    EventListener& operator=(const EventListener& other) {
        const_cast<int&>(id) = other.id;
        const_cast<GameData&>(data) = other.data;
        const_cast<Binder&>(binder) = other.binder;
        return *this;
    }

    int getId() const { return id; }
private:
    const int id;
    const GameData &data;
    const Binder &binder;
};