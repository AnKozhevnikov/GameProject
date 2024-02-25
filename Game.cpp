#include "Game.h"

Game::Game()  {
    data = GameData();
}

void Game::run() {
    FieldEvent new_event=FieldEvent();
    GameData new_data = new_event.run_event(data);
    data=new_data;
}