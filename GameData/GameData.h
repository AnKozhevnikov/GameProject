#pragma once

#include "Field.h"
#include "Hero.h"
#include "Inventory.h"
#include <memory>

class GameData {
public:
    GameData();
    GameData(const GameData& other);
    GameData& operator=(const GameData& other);
    
    void update(const GameData& delta);

    bool get_is_game_over() const;
    std::shared_ptr<bool> get_is_game_over_ptr() const;
    void set_is_game_over(bool newIsGameOver);

    Field get_field() const;
    std::shared_ptr<Field> get_field_ptr() const;
    void set_field(const Field& newField);

    std::vector<Hero> get_heroes() const;
    std::shared_ptr<std::vector<Hero>> get_heroes_ptr() const;
    void set_heroes(const std::vector<Hero>& newHeroes);

    Hero get_dead() const;
    std::shared_ptr<Hero> get_dead_ptr() const;
    void set_dead(const Hero& newDead);

    Inventory get_inventory() const;
    std::shared_ptr<Inventory> get_inventory_ptr() const;
    void set_inventory(const Inventory& newInventory);
private:
    std::shared_ptr<bool> isGameOver;
    std::shared_ptr<Field> field;
    std::shared_ptr<std::vector<Hero>> heroes;
    std::shared_ptr<Hero> dead;
    std::shared_ptr<Inventory> inventory;
};