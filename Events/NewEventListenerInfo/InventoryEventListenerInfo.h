#pragma once

#include "NewEventListenerInfo.h"

class InventoryEventListenerInfo : public NewEventListenerInfo {
public:
    InventoryEventListenerInfo() : NewEventListenerInfo() {
        eventType = "inventory";
    }
    InventoryEventListenerInfo(int parent, bool freeze) {
        this->parent = parent;
        this->freeze = freeze;
        eventType = "inventory";
    }
};