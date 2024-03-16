#include "ChestEventListener.h"
#include "Display.h"
#include "bitmap_image.hpp"
#include "Drawer.h"
#include "Randomizer.h"

ChestEventListener::ChestEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_field(parentData->get_field());
    data.set_heroes(parentData->get_heroes());
    data.set_inventory(parentData->get_inventory());
    init();
    //redraw();
}

void ChestEventListener::init() {
    Display display;
    bind('e', &ChestEventListener::open, this, "open the chest", 1);
}

Message ChestEventListener::open() {
    Inventory inventory = data.get_inventory();
    int resource = data.get_field_ptr()->get_depth() * 100;
    int deltas[4] = {0};
    int prices[4] = {75, 50, 150, 300};

    while (true) {
        int dice = Randomizer::getRandom(4);
        if (resource >= prices[dice]) {
            deltas[dice] += 1;
            resource -= prices[dice];
        } else {
            break;
        }
    }
    
    inventory.setGold(inventory.getGold() + resource);
    inventory.setHealthPotions(inventory.getHealthPotions() + deltas[0]);
    inventory.setBombs(inventory.getBombs() + deltas[1]);
    inventory.setFireBombs(inventory.getFireBombs() + deltas[2]);
    inventory.setStunBombs(inventory.getStunBombs() + deltas[3]);
    
    Display display;
    display.SendEvent(WindowEvent(WindowEvent::INFO, "Look, your loot!")); 
    
    data.set_inventory(inventory);
    return Message(data, NewEventListenerInfo(), true, id);
}
