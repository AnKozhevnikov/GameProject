#pragma once

#include "NewEventListenerInfo.h"

class BattleInventoryEventListenerInfo : public NewEventListenerInfo {
public:
    BattleInventoryEventListenerInfo() : NewEventListenerInfo() {};
    BattleInventoryEventListenerInfo(int parent, bool freeze) : NewEventListenerInfo(parent, freeze) {
        eventType = "battle inventory";
    };
    ~BattleInventoryEventListenerInfo() {};
};