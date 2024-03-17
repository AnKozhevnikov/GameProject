#pragma once

#include "Hero.h"
#include "HeroDrawer.h"

class HeroManager {
public:
    std::shared_ptr<Hero> hero;
    std::shared_ptr<HeroDrawer> drawer;
    bool team;

    int burn;
    int stun;
    bool selected;

    HeroManager(std::shared_ptr<Hero> newHero, std::shared_ptr<HeroDrawer> newDrawer, bool newTeam);
    HeroManager(const HeroManager &other);
    HeroManager& operator=(const HeroManager &other);

    bool isStunned() const;
    bool isBurned() const;

    void checkIfKilled();

    void select(bool flag);
    void applyStatus();
    void setBurn(int cnt);
    void setStun(int cnt);
    void applyDamage(int dmg);
    void applyHeal(double heal);
    void applyStatusHeal();

    void applyMove(int ability, std::vector<HeroManager*> toMoveAt);
};