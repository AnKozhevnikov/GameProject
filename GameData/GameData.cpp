#include "GameData.h"
#include "Field.h"

GameData::GameData() {
    field = nullptr;
}

GameData::GameData(const GameData& other) {
    field = std::make_unique<Field>(*other.field);
}

GameData& GameData::operator=(const GameData& other) {
    if (other.field != nullptr) field = std::make_unique<Field>(*other.field);
    else field = nullptr;
    return *this;
}

Field GameData::get_field() const {
    return *field;
}

const std::unique_ptr<Field> &GameData::get_field_ptr() const {
    return field;
}

void GameData::set_field(const Field& newField) {
    field = std::make_unique<Field>(newField);
}

void GameData::update(const GameData& delta) {
    if (delta.field != nullptr) {
        (*field).update(*delta.field);
    }
}