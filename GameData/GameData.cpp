#include "GameData.h"
#include "BattleSamples.h"

GameData::GameData() {
    isGameOver = std::make_shared<bool>(false);
    field = std::make_shared<Field>(1);
    heroes = std::make_shared<std::vector<Hero>>();
    heroes->push_back(SampleHeroes::warrior);
    heroes->push_back(SampleHeroes::mage);
    heroes->push_back(SampleHeroes::archer);
    dead = std::make_shared<Hero>(SampleHeroes::voidHero);
    inventory = std::make_shared<Inventory>();
}

GameData::GameData(const GameData& other) {
    isGameOver = std::make_shared<bool>(*other.isGameOver);
    field = std::make_shared<Field>(*other.field);
    heroes = std::make_shared<std::vector<Hero>>(*other.heroes);
    dead = std::make_shared<Hero>(*other.dead);
    inventory = std::make_shared<Inventory>(*other.inventory);
}

GameData& GameData::operator=(const GameData& other) {
    if (other.isGameOver != nullptr) isGameOver = std::make_shared<bool>(*other.isGameOver);
    else isGameOver = nullptr;

    if (other.field != nullptr) field = std::make_shared<Field>(*other.field);
    else field = nullptr;

    if (other.heroes != nullptr) heroes = std::make_shared<std::vector<Hero>>(*other.heroes);
    else heroes = nullptr;

    if (other.dead != nullptr) dead = std::make_shared<Hero>(*other.dead);
    else dead = nullptr;

    if (other.inventory != nullptr) inventory = std::make_shared<Inventory>(*other.inventory);
    else inventory = nullptr;

    return *this;
}

bool GameData::get_is_game_over() const {
    return *isGameOver;
}

std::shared_ptr<bool> GameData::get_is_game_over_ptr() const {
    return isGameOver;
}

void GameData::set_is_game_over(bool newIsGameOver) {
    isGameOver = std::make_shared<bool>(newIsGameOver);
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

std::vector<Hero> GameData::get_heroes() const {
    return *heroes;
}

std::shared_ptr<std::vector<Hero>> GameData::get_heroes_ptr() const {
    return heroes;
}

void GameData::set_heroes(const std::vector<Hero>& newHeroes) {
    heroes = std::make_shared<std::vector<Hero>>(newHeroes);
}

Hero GameData::get_dead() const {
    return *dead;
}

std::shared_ptr<Hero> GameData::get_dead_ptr() const {
    return dead;
}

void GameData::set_dead(const Hero& newDead) {
    dead = std::make_shared<Hero>(newDead);
}

Inventory GameData::get_inventory() const {
    return *inventory;
}

std::shared_ptr<Inventory> GameData::get_inventory_ptr() const {
    return inventory;
}

void GameData::set_inventory(const Inventory& newInventory) {
    inventory = std::make_shared<Inventory>(newInventory);
}

void GameData::update(const GameData& delta) {
    if (delta.isGameOver != nullptr) {
        isGameOver = std::make_shared<bool>(*delta.isGameOver);
    }

    if (delta.field != nullptr) {
        field->update(*delta.field);
    }

    if (delta.heroes != nullptr) {
        for (int i=0; i<delta.heroes->size(); i++) {
            if (i < heroes->size()) {
                (*heroes)[i].update((*delta.heroes)[i]);
            } else {
                heroes->push_back((*delta.heroes)[i]);
            }
        }
    }

    if (delta.dead != nullptr) {
        dead->update(*delta.dead);
    }

    if (delta.inventory != nullptr) {
        inventory->update(*delta.inventory);
    }
}