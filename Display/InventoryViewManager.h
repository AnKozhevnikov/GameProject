#pragma once
#include <memory>
#include "ItemDrawer.h"
#include "Item.h"

typedef std::shared_ptr<ItemDrawer> PItemDrawer;
typedef std::shared_ptr<Item> PItem;

namespace InventoryViewManager {
    PItemDrawer CreateItem(PItem pitem);
    void ClearAllItems();
    PItemDrawer GetItemDrawer(int x, int y);
    PItem GetItem(int x, int y);
};


