#pragma once

class Inventory {
public:
    Inventory() = default;
    Inventory(int gold, int healthPotions, int bombs, int fireBombs, int stunBombs);
    Inventory(const Inventory &other);
    Inventory& operator=(const Inventory &other);

    void update(const Inventory &delta);

    int getGold() const;
    void setGold(int newGold);

    int getHealthPotions() const;
    void setHealthPotions(int newHealthPotions);

    int getBombs() const;
    void setBombs(int newBombs);

    int getFireBombs() const;
    void setFireBombs(int newFireBombs);

    int getStunBombs() const;
    void setStunBombs(int newStunBombs);
private:
    int gold;
    int healthPotions;
    int bombs;
    int fireBombs;
    int stunBombs;
};