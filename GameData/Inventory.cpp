#include "Inventory.h"

Inventory::Inventory(Item gold, Item healthPotions, Item bombs, Item fireBombs, Item stunBombs) {
    this->gold = std::make_shared<Item>(gold);
    this->healthPotions = std::make_shared<Item>(healthPotions);
    this->bombs = std::make_shared<Item>(bombs);
    this->fireBombs = std::make_shared<Item>(fireBombs);
    this->stunBombs = std::make_shared<Item>(stunBombs);
}

Inventory::Inventory(const Inventory &other) {
    gold = other.gold;
    healthPotions = other.healthPotions;
    bombs = other.bombs;
    fireBombs = other.fireBombs;
    stunBombs = other.stunBombs;
}

Inventory& Inventory::operator=(const Inventory &other) {
    gold = other.gold;
    healthPotions = other.healthPotions;
    bombs = other.bombs;
    fireBombs = other.fireBombs;
    stunBombs = other.stunBombs;
    
    return *this;
}

Item Inventory::get_gold() const {
    return *gold;
}

std::shared_ptr<Item> Inventory::get_gold_ptr() const {
    return gold;
}

void Inventory::set_gold(const Item &newGold) {
    gold = std::make_shared<Item>(newGold);
}

Item Inventory::get_health_potions() const {
    return *healthPotions;
}

std::shared_ptr<Item> Inventory::get_health_potions_ptr() const {
    return healthPotions;
}

void Inventory::set_health_potions(const Item &newHealthPotions) {
    healthPotions = std::make_shared<Item>(newHealthPotions);
}

Item Inventory::get_bombs() const {
    return *bombs;
}

std::shared_ptr<Item> Inventory::get_bombs_ptr() const {
    return bombs;
}

void Inventory::set_bombs(const Item &newBombs) {
    bombs = std::make_shared<Item>(newBombs);
}

Item Inventory::get_fire_bombs() const {
    return *fireBombs;
}

std::shared_ptr<Item> Inventory::get_fire_bombs_ptr() const {
    return fireBombs;
}

void Inventory::set_fire_bombs(const Item &newFireBombs) {
    fireBombs = std::make_shared<Item>(newFireBombs);
}

Item Inventory::get_stun_bombs() const {
    return *stunBombs;
}

std::shared_ptr<Item> Inventory::get_stun_bombs_ptr() const {
    return stunBombs;
}

void Inventory::set_stun_bombs(const Item &newStunBombs) {
    stunBombs = std::make_shared<Item>(newStunBombs);
}

void Inventory::update(const Inventory &delta) {
    if (delta.gold != nullptr) {
        if (gold == nullptr) gold = std::make_shared<Item>();
        gold = delta.gold;
    }
    if (delta.healthPotions != nullptr) {
        if (healthPotions == nullptr) healthPotions = std::make_shared<Item>();
        healthPotions = delta.healthPotions;
    }
    if (delta.bombs != nullptr) {
        if (bombs == nullptr) bombs = std::make_shared<Item>();
        bombs = delta.bombs;
    }
    if (delta.fireBombs != nullptr) {
        if (fireBombs == nullptr) fireBombs = std::make_shared<Item>();
        fireBombs = delta.fireBombs;
    }
    if (delta.stunBombs != nullptr) {
        if (stunBombs == nullptr) stunBombs = std::make_shared<Item>();
        stunBombs = delta.stunBombs;
    }
}