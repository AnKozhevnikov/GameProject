#pragma once

#include "GameData.h"

class Game {
public:
    Game();

    void run();
private:
    std::string event;
    GameData data;
};