#pragma once

#include "Game.h"

class Monitor {
public:
    Monitor();
    void run();
private:
    std::string current_event;
    Game game;
};