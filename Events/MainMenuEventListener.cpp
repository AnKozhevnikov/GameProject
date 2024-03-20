#include "MainMenuEventListener.h"
#include "Display.h"
#include "Drawer.h"
#include "FieldEventListenerInfo.h"
#include "BattleEventListenerInfo.h"
#include "InventoryEventListenerInfo.h"
#include "NpcEventListenerInfo.h"
#include "BattleSamples.h"
#include "ReviveEventListenerInfo.h"
#include "ReviveEventListener.h"

MainMenuEventListener::MainMenuEventListener(const int newId, const int parent, const GameData *data, Binder *binder) : EventListener(newId, parent, data, binder) {
    bind(10, &MainMenuEventListener::startGame, this, "start game");
    bind(27, &MainMenuEventListener::exit, this, "exit");
    bind('b', &MainMenuEventListener::playbattleSample, this, "play battle sample");
    bind('i', &MainMenuEventListener::openInventory, this, "open inventory");
    bind('e', &MainMenuEventListener::NpcEncounter, this, "encounter NPC");
    bind('r', &MainMenuEventListener::revive, this, "revive");
    redraw();
}

void MainMenuEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();
    display.DrawSprite(Drawer::getSprite("Logo"), 0, 0);
}

Message MainMenuEventListener::startGame() {
    return Message(GameData(true), std::make_shared<FieldEventListenerInfo>(id, true), false, id);
}

Message MainMenuEventListener::exit() {
    data.set_is_game_over(true);
    return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
}

Message MainMenuEventListener::playbattleSample() {
    return Message(GameData(true), std::make_shared<BattleEventListenerInfo>(id, true, std::vector<Hero>{SampleHeroes::warrior, SampleHeroes::mage, SampleHeroes::archer}), false, id);
}

Message MainMenuEventListener::openInventory() {
    return Message(GameData(true), std::make_shared<InventoryEventListenerInfo>(id, true), false, id);
}

Message MainMenuEventListener::NpcEncounter() {
    return Message(GameData(true), std::make_shared<NpcEventListenerInfo>(id, true, SampleHeroes::mage, 50), false, id);
}

Message MainMenuEventListener::revive() {
    return Message(GameData(true), std::make_shared<ReviveEventListenerInfo>(id, true, 50), false, id);
}