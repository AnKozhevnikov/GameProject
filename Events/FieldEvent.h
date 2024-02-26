#pragma once

#include "Event.h"

class FieldEvent : public Event {
public:
    void run_event(GameData &data);
};