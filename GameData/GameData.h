#pragma once

#include "Field.h"
#include <memory>

class GameData {
public:
    GameData();
    GameData(const GameData& other);
    GameData& operator=(const GameData& other);
    
    void update(const GameData& delta);

    Field get_field() const;
    std::shared_ptr<Field> get_field_ptr() const;
    void set_field(const Field& newField);
private:
    std::shared_ptr<Field> field;
};