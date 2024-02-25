#pragma once

#include "Event.h"

class FieldEvent : public Event {
public:
    GameData run_event(GameData data);
};