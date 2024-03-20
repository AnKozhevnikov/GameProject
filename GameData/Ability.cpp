#include "Ability.h"
#include <vector>

#include <string>
#include <vector>

Ability::Ability(std::string name, std::string hint, std::vector<std::vector<unsigned>> sprite, bool team, bool multitarget, double damage, double heal, bool healStatus, int burn, int stun) {
    this->name = name;
    this->hint = hint;
    this->sprite = sprite;
    this->team = team;
    this->multitarget = multitarget;
    this->damage = damage;
    this->heal = heal;
    this->healStatus = healStatus;
    this->burn = burn;
    this->stun = stun;
}

Ability::Ability(const Ability &other) {
    name = other.name;
    hint = other.hint;
    sprite = other.sprite;
    team = other.team;
    multitarget = other.multitarget;
    damage = other.damage;
    heal = other.heal;
    healStatus = other.healStatus;
    burn = other.burn;
    stun = other.stun;
}

Ability& Ability::operator=(const Ability &other) {
    name = other.name;
    hint = other.hint;
    sprite = other.sprite;
    team = other.team;
    multitarget = other.multitarget;
    damage = other.damage;
    heal = other.heal;
    healStatus = other.healStatus;
    burn = other.burn;
    stun = other.stun;
    return *this;
}

std::string Ability::get_name() const {
    return name;
}

std::string Ability::get_hint() const {
    return hint;
}

std::vector<std::vector<unsigned int>> Ability::get_sprite() const {
    return sprite;
}

bool Ability::get_team() const {
    return team;
}

bool Ability::get_multitarget() const {
    return multitarget;
}

double Ability::get_damage() const {
    return damage;
}

double Ability::get_heal() const {
    return heal;
}

int Ability::get_burn() const {
    return burn;
}

int Ability::get_stun() const {
    return stun;
}

bool Ability::get_heal_status() const {
    return healStatus;
}

