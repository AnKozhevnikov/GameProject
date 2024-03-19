#pragma once

#include "NewEventListenerInfo.h"

class InventoryEventListenerInfo : public NewEventListenerInfo {
public:
    InventoryEventListenerInfo(int parent, bool freeze) {
        this->parent = parent;
        this->freeze = freeze;
        eventType = "inventory";
    }
};