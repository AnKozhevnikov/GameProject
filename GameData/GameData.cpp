#include "GameData.h"

GameData::GameData() {
    field = std::make_shared<Field>(1);
}

GameData::GameData(const GameData& other) {
    field = std::make_shared<Field>(*other.field);
}

GameData& GameData::operator=(const GameData& other) {
    if (other.field != nullptr) field = std::make_shared<Field>(*other.field);
    else field = nullptr;
    return *this;
}

Field GameData::get_field() const {
    return *field;
}

std::shared_ptr<Field> GameData::get_field_ptr() const {
    return field;
}

void GameData::set_field(const Field& newField) {
    field = std::make_shared<Field>(newField);
}

void GameData::update(const GameData& delta) {
    if (delta.field != nullptr) {
        field->update(*delta.field);
    }
}