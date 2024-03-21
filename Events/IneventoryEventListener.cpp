#include "InventoryEventListener.h"
#include "InventoryViewManager.h"
#include "HeroDrawer.h"
#include "Display.h"

#include <memory>

InventoryEventListener::InventoryEventListener(const int newId, const int parent, const GameData *parentData, Binder *binder) : EventListener(newId, parent, parentData, binder) {
    this->data.set_heroes(parentData->get_heroes());
    this->data.set_dead(parentData->get_dead());
    this->data.set_inventory(parentData->get_inventory());
    drawers.resize(3);
    redraw();
    bind(27, &InventoryEventListener::exit, this, "exit");
    bind(-1, &InventoryEventListener::update, this, "update");
}

void drawAttributes(std::shared_ptr<HeroDrawer> heroDrawer, std::shared_ptr<Hero> hero) {
    heroDrawer->SetName(hero->get_name());
    heroDrawer->SetHp(hero->get_hp(), hero->get_maxHp());
    heroDrawer->SetDmg(hero->get_dmg());
    heroDrawer->SetAttention(hero->get_initiative());
    heroDrawer->SetInitiative(hero->get_initiative());
}

void InventoryEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();
    InventoryViewManager::ClearAllItems();
    InventoryViewManager::CreateItem(data.get_inventory_ptr()->get_gold_ptr());
    InventoryViewManager::CreateItem(data.get_inventory_ptr()->get_health_potions_ptr());
    InventoryViewManager::CreateItem(data.get_inventory_ptr()->get_bombs_ptr());
    InventoryViewManager::CreateItem(data.get_inventory_ptr()->get_fire_bombs_ptr());
    InventoryViewManager::CreateItem(data.get_inventory_ptr()->get_stun_bombs_ptr());

    if (data.get_heroes_ptr()->at(0).get_name() != "void") {
        drawers[0] = std::make_shared<HeroDrawer>(std::make_shared<Hero>(data.get_heroes_ptr()->at(0)), 47, 31);
        drawAttributes(drawers[0], std::make_shared<Hero>(data.get_heroes_ptr()->at(0)));
    }

    if (data.get_heroes_ptr()->at(1).get_name() != "void") {
        drawers[1] = std::make_shared<HeroDrawer>(std::make_shared<Hero>(data.get_heroes_ptr()->at(1)), 66, 31);
        drawAttributes(drawers[1], std::make_shared<Hero>(data.get_heroes_ptr()->at(1)));
    }

    if (data.get_heroes_ptr()->at(2).get_name() != "void") {
        drawers[2] = std::make_shared<HeroDrawer>(std::make_shared<Hero>(data.get_heroes_ptr()->at(2)), 85, 31);
        drawAttributes(drawers[2], std::make_shared<Hero>(data.get_heroes_ptr()->at(2)));
    }

    if (data.get_dead_ptr()->get_name() != "void") {
        deadDrawer = std::make_shared<HeroDrawer>(data.get_dead_ptr(), 15, 31);
        drawAttributes(deadDrawer, data.get_dead_ptr());
        deadDrawer->ApplyEffect(VisualEffect::DEAD, true);
    }
}

Message InventoryEventListener::exit() {
    InventoryViewManager::ClearAllItems();
    return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
}

Message InventoryEventListener::update() {
    if (deadDrawer != nullptr) deadDrawer->UpdateAnimations();
    return Message();
}