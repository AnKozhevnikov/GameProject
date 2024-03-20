#pragma once

#include "EventListener.h"

class InventoryEventListener : public EventListener {
public:
    InventoryEventListener() : EventListener() {};
    InventoryEventListener(const int newId, const int parent, const GameData *data, Binder *binder);

private:
    std::vector<std::shared_ptr<HeroDrawer>> drawers;
    std::shared_ptr<HeroDrawer> deadDrawer;
    void redraw();
    Message exit();
    Message update();
};