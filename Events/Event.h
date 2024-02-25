#pragma once

#include <string>
#include "GameData.h"

class Event {
private:
    virtual GameData run_event(GameData data) {return data;}
};