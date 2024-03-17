#pragma once

#include <string>
#include <vector>

class Ability {
public:
    Ability() = default;
    Ability(std:: string name, std::string hint, std::vector<std::vector<unsigned>> sprite, bool team, bool multitarget, double damage, double heal, bool healStatus, int burn, int stun);
    Ability(const Ability &other);
    Ability& operator=(const Ability &other);

    std::string get_name() const;
    std::string get_hint() const;
    std::vector<std::vector<unsigned int>> get_sprite() const;
    bool get_team() const;
    bool get_multitarget() const;
    double get_damage() const;
    double get_heal() const;
    int get_burn() const;
    int get_stun() const;
private:
    std::string name;
    std::string hint;
    std::vector<std::vector<unsigned int>> sprite;
    bool team; //true if apply to self, false if apply to enemy
    bool multitarget; //true if apply to all enemies, false if apply to one enemy
    double damage; //proportion of unit's dmg, 0 if don't deal damage
    double heal; //proportion of unit's maxHp, 0 if don't heal
    bool healStatus; //true if heal all status effects, false if don't heal
    int burn; //amount of steps to burn, 0 if don't burn
    int stun; //amount of steps to stun, 0 if don't stun
};