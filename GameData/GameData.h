#pragma once

#include "Field.h"

class GameData {
public:
    GameData();
    GameData& operator=(const GameData& other) = default;
private:
    Field field;
};