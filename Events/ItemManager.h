#pragma once

#include "Item.h"
#include "ItemDrawer.h"
#include <memory>

class ItemManager {
public:
    std::shared_ptr<Item> item;
    std::shared_ptr<ItemDrawer> drawer;
    bool selected;
    
    ItemManager(std::shared_ptr<Item> newItem, std::shared_ptr<ItemDrawer> newDrawer, bool newSelected) : item(newItem), drawer(newDrawer), selected(newSelected) {};
    ItemManager(const ItemManager &other) : item(other.item), drawer(other.drawer), selected(other.selected) {};
    ItemManager& operator=(const ItemManager &other) {
        item = other.item;
        drawer = other.drawer;
        selected = other.selected;
        return *this;
    };
    ~ItemManager() = default;

    void select(bool flag) {
        selected=flag;
        drawer->Select(flag);
    }
};