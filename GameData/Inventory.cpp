#include "Inventory.h"

Inventory::Inventory(int gold, int healthPotions, int bombs, int fireBombs, int stunBombs) {
    this->gold = gold;
    this->healthPotions = healthPotions;
    this->bombs = bombs;
    this->fireBombs = fireBombs;
    this->stunBombs = stunBombs;
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

int Inventory::getGold() const {
    return gold;
}

void Inventory::setGold(int newGold) {
    gold = newGold;
}

int Inventory::getHealthPotions() const {
    return healthPotions;
}

void Inventory::setHealthPotions(int newHealthPotions) {
    healthPotions = newHealthPotions;
}

int Inventory::getBombs() const {
    return bombs;
}

void Inventory::setBombs(int newBombs) {
    bombs = newBombs;
}

int Inventory::getFireBombs() const {
    return fireBombs;
}

void Inventory::setFireBombs(int newFireBombs) {
    fireBombs = newFireBombs;
}

int Inventory::getStunBombs() const {
    return stunBombs;
}

void Inventory::setStunBombs(int newStunBombs) {
    stunBombs = newStunBombs;
}

void Inventory::update(const Inventory& delta) {
    gold = delta.gold;
    healthPotions = delta.healthPotions;
    bombs = delta.bombs;
    fireBombs = delta.fireBombs;
    stunBombs = delta.stunBombs;
}