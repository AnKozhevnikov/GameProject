#pragma once

#include "Game.h"
#include "Display.h"

class Manager {
public:
    Manager();
    void start_game();
private:
    Display display;
    Game game;
};