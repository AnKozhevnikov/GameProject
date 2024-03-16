#include "Ability.h"

Ability::Ability(std::string name, std::string hint, bool team, bool multitarget, double damage, double heal, bool healStatus, int burn, int stun) {
    this->name = name;
    this->hint = hint;
    this->team = team;
    this->multitarget = multitarget;
    this->damage = damage;
    this->heal = heal;
    this->healStatus = healStatus;
    this->burn = burn;
    this->stun = stun;
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

