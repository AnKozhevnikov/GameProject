#pragma once

#include "Inventory.h"
#include "EventListener.h"
#include "ItemManager.h"

class BattleInventoryEventListener : public EventListener {
public:
    BattleInventoryEventListener() : EventListener() {};
    BattleInventoryEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    std::vector<std::vector<std::shared_ptr<ItemManager>>> items;
    int x, y;
    Message move(int direction);
    Message apply();
    void redraw();
    Message exit();
};