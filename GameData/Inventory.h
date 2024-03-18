#pragma once

#include "Item.h"
#include <memory>

class Inventory {
public:
    Inventory() = default;
    Inventory(Item gold, Item healthPotions, Item bombs, Item fireBombs, Item stunBombs);
    Inventory(const Inventory &other);
    Inventory& operator=(const Inventory &other);

    Item get_gold() const;
    std::shared_ptr<Item> get_gold_ptr() const;
    void set_gold(const Item &newGold);

    Item get_health_potions() const;
    std::shared_ptr<Item> get_health_potions_ptr() const;
    void set_health_potions(const Item &newHealthPotions);

    Item get_bombs() const;
    std::shared_ptr<Item> get_bombs_ptr() const;
    void set_bombs(const Item &newBombs);

    Item get_fire_bombs() const;
    std::shared_ptr<Item> get_fire_bombs_ptr() const;
    void set_fire_bombs(const Item &newFireBombs);

    Item get_stun_bombs() const;
    std::shared_ptr<Item> get_stun_bombs_ptr() const;
    void set_stun_bombs(const Item &newStunBombs);

    void update(const Inventory &delta);
private:
    std::shared_ptr<Item> gold;
    std::shared_ptr<Item> healthPotions;
    std::shared_ptr<Item> bombs;
    std::shared_ptr<Item> fireBombs;
    std::shared_ptr<Item> stunBombs;
};