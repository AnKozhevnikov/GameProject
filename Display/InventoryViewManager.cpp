#include "InventoryViewManager.h"
#include "InventoryConstants.h"
#include <array>
#include <stdexcept>

using std::array, std::shared_ptr;

namespace InventoryViewManager {
    array<PItemDrawer, InventoryConstants::ItemsInRow * InventoryConstants::ItemsInColumn> itemDrawers = {nullptr};
    array<PItem, InventoryConstants::ItemsInRow * InventoryConstants::ItemsInColumn> items = {nullptr};
    int lastItemIdx = 0;
    PItemDrawer CreateItem(PItem pitem) {
        items[lastItemIdx] = std::move(pitem);
        int x = (lastItemIdx % InventoryConstants::ItemsInRow) * (InventoryConstants::ItemBoxWidth + InventoryConstants::ColumnsBetweenItems);
        int y = (lastItemIdx / InventoryConstants::ItemsInRow) * (InventoryConstants::ItemBoxHeight + InventoryConstants::RowsBetweenItems);
        itemDrawers[lastItemIdx] = std::make_shared<ItemDrawer>(items[lastItemIdx],
                                                                x, y);
        return itemDrawers[lastItemIdx];
    }
    void RemoveItem(int x, int y) {
        int idx = (y / (InventoryConstants::ItemBoxHeight + InventoryConstants::RowsBetweenItems)) * InventoryConstants::ItemsInRow +
                  (x / (InventoryConstants::ItemBoxWidth + InventoryConstants::ColumnsBetweenItems));
        items[idx] = nullptr;
        itemDrawers[idx] = nullptr;
    }
    void ClearAllItems() {
        for(int i = 0; i < InventoryConstants::ItemsInRow * InventoryConstants::ItemsInColumn; ++i) {
            RemoveItem(i % InventoryConstants::ItemsInRow, i / InventoryConstants::ItemsInRow);
        }
    }
    PItemDrawer GetItemDrawer(int x, int y) {
        int id = (y / (InventoryConstants::ItemBoxHeight + InventoryConstants::RowsBetweenItems)) * InventoryConstants::ItemsInRow +
                 (x / (InventoryConstants::ItemBoxWidth + InventoryConstants::ColumnsBetweenItems));
        if(itemDrawers[id] == nullptr) {
            throw std::runtime_error("No item to get");
        }
        return itemDrawers[id];
    }
    PItem GetItem(int x, int y) {
        int id = (y / (InventoryConstants::ItemBoxHeight + InventoryConstants::RowsBetweenItems)) * InventoryConstants::ItemsInRow +
                 (x / (InventoryConstants::ItemBoxWidth + InventoryConstants::ColumnsBetweenItems));
        if(items[id] == nullptr) {
            throw std::runtime_error("No item to get");
        }
        return items[id];
    }
};
