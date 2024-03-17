#pragma once

#include <string>

class NewEventListenerInfo {
public:
    NewEventListenerInfo() {
        eventType = "void";
        parent = 0;
        freeze = false;
    };
    NewEventListenerInfo(int parent, bool freeze) {
        this->parent = parent;
        this->freeze = freeze;
    };
    virtual ~NewEventListenerInfo() {};
    std::string eventType;
    int parent;
    bool freeze;
};