#pragma once

#include <string>
#include "GameData.h"

class Event {
private:
    virtual void run_event(GameData &data) {}
};