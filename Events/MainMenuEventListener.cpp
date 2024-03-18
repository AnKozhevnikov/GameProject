#include "MainMenuEventListener.h"
#include "Display.h"
#include "Drawer.h"
#include "FieldEventListenerInfo.h"
#include "BattleEventListenerInfo.h"
#include "BattleSamples.h"

MainMenuEventListener::MainMenuEventListener(const int newId, const int parent, const GameData *data, Binder *binder) : EventListener(newId, parent, data, binder) {
    this->data.set_dead(data->get_dead());
    this->data.set_is_game_over(data->get_is_game_over());
    this->data.set_heroes(data->get_heroes());
    this->data.set_field(data->get_field());
    this->data.set_inventory(data->get_inventory());

    bind(10, &MainMenuEventListener::startGame, this, "start game");
    bind(27, &MainMenuEventListener::exit, this, "exit");
    bind('b', &MainMenuEventListener::playbattleSample, this, "play battle sample");
    redraw();
}

void MainMenuEventListener::redraw() {
    Display display;
    display.DrawSprite(Drawer::getSprite("Logo"), 0, 0);
}

Message MainMenuEventListener::startGame() {
    return Message(data, std::make_shared<FieldEventListenerInfo>(id, true), false, id);
}

Message MainMenuEventListener::exit() {
    data.set_is_game_over(true);
    return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
}

Message MainMenuEventListener::playbattleSample() {
    return Message(data, std::make_shared<BattleEventListenerInfo>(id, true, std::vector<Hero>{SampleHeroes::warrior, SampleHeroes::mage, SampleHeroes::archer}), false, id);
}