#include "MainMenuEventListener.h"
#include "Display.h"
#include "Drawer.h"
#include "FieldEventListenerInfo.h"
#include "BattleEventListenerInfo.h"
#include "InventoryEventListenerInfo.h"
#include "NpcEventListenerInfo.h"
#include "AltarEventListenerInfo.h"
#include "ReviveEventListenerInfo.h"
#include "BattleSamples.h"

MainMenuEventListener::MainMenuEventListener(const int newId, const int parent, const GameData *data, Binder *binder) : EventListener(newId, parent, data, binder) {
    bind(10, &MainMenuEventListener::startGame, this, "start game");
    bind(27, &MainMenuEventListener::exit, this, "exit");

    this->data = GameData(id);

    redraw();
}

void MainMenuEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();
    display.DrawSprite(Drawer::getSprite("Logo"), 0, 0);
}

Message MainMenuEventListener::startGame() {
    return Message(GameData(id), std::make_shared<FieldEventListenerInfo>(id, true), false, id);
}

Message MainMenuEventListener::exit() {
    data.set_is_game_over(true);
    return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
}