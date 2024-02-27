#include "GameData.h"
#include "Field.h"

GameData::GameData() {
    field = Field();
}

const Field& GameData::get_field() const {
    return field;
}

void GameData::update(const Delta& delta) {
    //TODO: implement
}