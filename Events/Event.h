#pragma once

#include <string>
#include <memory>
#include "GameData.h"

class Event {
public:
    Event(GameData &data) : data(data) {};
private:
    GameData &data;
    virtual std::shared_ptr<void> run_event() = 0;
};