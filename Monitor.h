#pragma once

#include "Game.h"

class Monitor {
public:
    Monitor();
    void run();
    char get_last_pressed();
private:
    std::string current_event;
    Game game;
};