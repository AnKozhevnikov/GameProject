#include "BattleInventoryEventListener.h"
#include "InventoryConstants.h"
#include "InventoryViewManager.h"
#include "Display.h"

BattleInventoryEventListener::BattleInventoryEventListener(const int newId, const int parent, const GameData *data, Binder *binder) : EventListener(newId, parent, data, binder) {
    this->data.set_inventory(parentData->get_inventory());
    x = 0;
    y = 0;
    items.resize(InventoryConstants::ItemsInColumn, std::vector<std::shared_ptr<ItemManager>>(InventoryConstants::ItemsInRow));
    items[0][0] = std::make_shared<ItemManager>(this->data.get_inventory_ptr()->get_health_potions_ptr(), InventoryViewManager::CreateItem(this->data.get_inventory_ptr()->get_health_potions_ptr()), false);
    items[0][1] = std::make_shared<ItemManager>(this->data.get_inventory_ptr()->get_bombs_ptr(), InventoryViewManager::CreateItem(this->data.get_inventory_ptr()->get_bombs_ptr()), false);
    items[0][2] = std::make_shared<ItemManager>(this->data.get_inventory_ptr()->get_fire_bombs_ptr(), InventoryViewManager::CreateItem(this->data.get_inventory_ptr()->get_fire_bombs_ptr()), false);
    items[0][3] = std::make_shared<ItemManager>(this->data.get_inventory_ptr()->get_stun_bombs_ptr(), InventoryViewManager::CreateItem(this->data.get_inventory_ptr()->get_stun_bombs_ptr()), false);

    items[0][0]->select(true);

    bind('w', &BattleInventoryEventListener::move, this, "move up", 1);
    bind('a', &BattleInventoryEventListener::move, this, "move left", 2);
    bind('s', &BattleInventoryEventListener::move, this, "move down", 3);
    bind('d', &BattleInventoryEventListener::move, this, "move right", 4);
    bind(27, &BattleInventoryEventListener::exit, this, "exit");
    bind(10, &BattleInventoryEventListener::apply, this, "apply");
}

void BattleInventoryEventListener::redraw() {
    InventoryViewManager::ClearAllItems();
    for (int i=0; i<InventoryConstants::ItemsInColumn; i++) {
        for (int j=0; j<InventoryConstants::ItemsInRow; j++) {
            items[i][j] = std::make_shared<ItemManager>(std::make_shared<Item>(), InventoryViewManager::CreateItem(items[i][j]->item), false);
            if (items[i][j]->selected) {
                items[i][j]->select(true);
            }
        }
    }
}

Message BattleInventoryEventListener::move(int direction) {
    int dx = 0;
    int dy = 0;
    if (direction == 1) {
        dy = -1;
    } else if (direction == 2) {
        dx = -1;
    } else if (direction == 3) {
        dy = 1;
    } else if (direction == 4) {
        dx = 1;
    }

    if (0 <= x+dx && x+dx < InventoryConstants::ItemsInRow && 0 <= y+dy && y+dy < InventoryConstants::ItemsInColumn && items[y+dy][x+dx] != nullptr) {
        items[y][x]->select(false);
        x += dx;
        y += dy;
        items[y][x]->select(true);
    }

    return Message();
}

Message BattleInventoryEventListener::apply() {
    Display display;
    if (items[y][x]->item->get_amount() != 0) {
        items[y][x]->item->set_amount(items[y][x]->item->get_amount()-1);
        data.set_potion(items[y][x]->item->get_ability());
        InventoryViewManager::ClearAllItems();
        display.SendEvent(WindowEvent(WindowEvent::ACTION, items[y][x]->item->get_name() + " used"));
        return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
    }
    else {
        display.SendEvent(WindowEvent(WindowEvent::ACTION, "No left"));
        return Message();
    }
}

Message BattleInventoryEventListener::exit() {
    InventoryViewManager::ClearAllItems();
    return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
}