#include "Game.h"
#include "FieldEvent.h"
#include "EmptyEvent.h"

Game::Game()  {
    data = GameData();
    event = "FieldEvent";
}

void Game::run() {
    if (event == "FieldEvent") {
        FieldEvent field_event;
        field_event.run_event(data);
    } else if (event == "EmptyEvent") {
        EmptyEvent empty_event;
        empty_event.run_event(data);
    }
}