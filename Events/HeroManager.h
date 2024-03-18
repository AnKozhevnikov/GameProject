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
    bool dead;
    bool selectedAsSource;
    bool selectedAsTarget;

    HeroManager(std::shared_ptr<Hero> newHero, std::shared_ptr<HeroDrawer> newDrawer, bool newTeam);
    HeroManager(const HeroManager &other);
    HeroManager& operator=(const HeroManager &other);

    bool isStunned() const;
    bool isBurned() const;
    bool isDead() const;

    bool isSelectedAsSource() const;
    bool isSelectedAsTarget() const;

    void checkIfKilled();

    void selectAsSource(bool flag);
    void selectAsTarget(bool flag);
    
    void applyStatus();
    void setBurn(int cnt);
    void setStun(int cnt);
    void applyDamage(int dmg);
    void applyHeal(double heal);
    void applyStatusHeal();

    void applyMove(int ability, std::vector<std::shared_ptr<HeroManager>> toMoveAt);
};