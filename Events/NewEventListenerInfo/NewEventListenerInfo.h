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

class FieldEventListenerInfo : public NewEventListenerInfo {
public:
    FieldEventListenerInfo() {
        eventType = "field";
        depth = 0;
    };
    int depth;
};