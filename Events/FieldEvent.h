#pragma once

#include "Event.h"

class FieldEvent : public Event {
public:
    FieldEvent(GameData &data, char button) : Event(data), button(button) {};
    std::shared_ptr<void> run_event() override;
private:
    char button;
};