#pragma once

#include "Field.h"

class GameData {
public:
    GameData();
    GameData& operator=(const GameData& other) = default;

    const Field& get_field() const;
private:
    Field field;
};