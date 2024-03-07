#pragma once

#include <string>

class NewEventListenerInfo {
public:
    NewEventListenerInfo() {
        eventType = "void";
        parent = 0;
    };
    std::string eventType;
    int parent;
};