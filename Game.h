#pragma once

#include "GameData.h"
#include "FieldEvent.h"

class Game {
public:
    Game();

    void run();
private:
    GameData data;
};