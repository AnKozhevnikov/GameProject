#include "GameData.h"
#include "BattleSamples.h"
#include "Randomizer.h"

GameData::GameData(bool flag) {
    if (flag) {
        isGameOver = std::make_shared<bool>(false);

        heroes = std::make_shared<std::vector<Hero>>(Randomizer::getRandomSquad(1, 15, 5, 3, true, 0));

        field = std::make_shared<Field>(1, heroes);

        dead = std::make_shared<Hero>(SampleHeroes::voidHero);

        inventory = std::make_shared<Inventory>();
        inventory->set_gold(SampleItems::gold);
        inventory->set_health_potions(SampleItems::healthPotions);
        inventory->set_bombs(SampleItems::bombs);
        inventory->set_fire_bombs(SampleItems::fireBombs);
        inventory->set_stun_bombs(SampleItems::stunBombs);

        potion = std::make_shared<Ability>(SampleAbilities::voidAbility);
    }
    else {
        isGameOver = nullptr;
        field = nullptr;
        heroes = nullptr;
        dead = nullptr;
        inventory = nullptr;
        potion = nullptr;
    }
}

GameData::GameData(const GameData& other) {
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
    if (other.potion != nullptr) potion = std::make_shared<Ability>(*other.potion);
    else potion = nullptr;
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

    if (other.potion != nullptr) potion = std::make_shared<Ability>(*other.potion);
    else potion = nullptr;

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

Ability GameData::get_potion() const {
    return *potion;
}

std::shared_ptr<Ability> GameData::get_potion_ptr() const {
    return potion;
}

void GameData::set_potion(const Ability& newPotion) {
    potion = std::make_shared<Ability>(newPotion);
}

void GameData::update(const GameData& delta) {
    if (delta.isGameOver != nullptr) {
        isGameOver = std::make_shared<bool>(*delta.isGameOver);
    }

    if (delta.field != nullptr) {
        if (field == nullptr) field = std::make_shared<Field>();
        field->update(*delta.field);
    }

    if (delta.heroes != nullptr) {
        if (heroes == nullptr) heroes = std::make_shared<std::vector<Hero>>();
        for (int i=0; i<delta.heroes->size(); i++) {
            if (i < heroes->size()) {
                heroes->at(i).update((*delta.heroes)[i]);
            } else {
                heroes->push_back((*delta.heroes)[i]);
            }
        }
    }

    if (delta.dead != nullptr) {
        if (dead == nullptr) dead = std::make_shared<Hero>();
        dead->update(*delta.dead);
    }

    if (delta.inventory != nullptr) {
        if (inventory == nullptr) inventory = std::make_shared<Inventory>();
        inventory->update(*delta.inventory);
    }

    if (delta.potion != nullptr) {
        if (potion == nullptr) potion = std::make_shared<Ability>();
        potion = std::make_shared<Ability>(*delta.potion);
    }
}