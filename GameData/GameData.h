#pragma once

#include "Field.h"
#include "Delta.h"

class GameData {
public:
    GameData();
    GameData& operator=(const GameData& other) = default;
    void update(const Delta& delta);

    const Field& get_field() const;
private:
    Field field;
};