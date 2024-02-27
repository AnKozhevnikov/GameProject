#pragma once

#include "Game.h"

class Monitor {
public:
    Monitor();
    void start_game();
private:
    Game game;
};