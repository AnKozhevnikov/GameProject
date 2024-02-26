#pragma once

#include "Event.h"

class EmptyEvent : public Event {
public:
    void run_event(GameData &data);
};