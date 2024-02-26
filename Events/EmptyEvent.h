#pragma once

#include "Event.h"

class EmptyEvent : public Event {
public:
    EmptyEvent(GameData &data) : Event(data) {};
    std::shared_ptr<void> run_event() override;
};