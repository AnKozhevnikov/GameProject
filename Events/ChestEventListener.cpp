#include "ChestEventListener.h"
#include "Display.h"
#include "Drawer.h"
#include "Randomizer.h"

ChestEventListener::ChestEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_inventory(parentData->get_inventory());
    
    chestStatus = "closed";
    init();
    redraw();
}

void ChestEventListener::init() {
    Display display;
    bind('e', &ChestEventListener::open, this, "open the chest", 0);
}

Message ChestEventListener::open(int value) {
    chestStatus = "opened";
    Display display;
    Inventory inventory = data.get_inventory();
    int chest_value = 200;
    int deltas[4] = {0};
    int prices[4] = {75, 50, 150, 200};

    while (true) {
        int dice = Randomizer::getRandom(4);
        if (chest_value >= prices[dice]) {
            deltas[dice] += 1;
            chest_value -= prices[dice];
        } else {
            break;
        }
    }
    
    inventory.get_gold_ptr()->set_amount(inventory.get_gold().get_amount() + chest_value);
    inventory.get_health_potions_ptr()->set_amount(inventory.get_health_potions().get_amount() + deltas[0]);
    inventory.get_bombs_ptr()->set_amount(inventory.get_bombs().get_amount() + deltas[1]);
    inventory.get_fire_bombs_ptr()->set_amount(inventory.get_fire_bombs().get_amount() + deltas[2]);
    inventory.get_stun_bombs_ptr()->set_amount(inventory.get_stun_bombs().get_amount() + deltas[3]);
 
    display.SendEvent(WindowEvent(WindowEvent::REPLY, "You've found " + std::to_string(chest_value) + " gold, " + std::to_string(deltas[0]) + " health potions, " + std::to_string(deltas[1]) + " bombs, " + std::to_string(deltas[2]) + " fire bombs and " + std::to_string(deltas[3]) + " stun bombs"));

    data.set_inventory(inventory);
 
    redraw();

    unbind(&ChestEventListener::open, this, "open the chest", 0);
    bind('e', &ChestEventListener::exit, this, "continue");

    return Message(data, std::make_shared<NewEventListenerInfo>(), false, id);
}

Message ChestEventListener::exit() {
    return Message(GameData(), std::make_shared<NewEventListenerInfo>(), true, id);
}

void ChestEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();
    if (chestStatus == "closed") {
        display.DrawSprite(Drawer::getSprite("chest"), 23, 10);
    } else if (chestStatus == "opened") {
        display.DrawSprite(Drawer::getSprite("chest_open"), 23, 10);
    }
}