#pragma once

#include "EventListener.h"
#include "HeroManager.h"
#include "GameData.h"
#include "AbilityManager.h"
#include <vector>

class BattleEventListener : public EventListener {
public:
    BattleEventListener() : EventListener() {};
    BattleEventListener(const int newId, const int parent, const GameData *data, Binder *binder, std::vector<Hero> enemies);
private:
    std::vector<Hero> enemies;
    std::vector<HeroManager> we;
    std::vector<HeroManager> they;
    int currentInOrder;
    std::vector<std::shared_ptr<HeroManager>> order;
    std::vector<std::shared_ptr<AbilityManager>> abilities;

    int step; // 0 - select ability, 1 - select target
    bool moveFinished;
    bool teamSelect;
    int heroSelected;
    int abilitySelected;

    void redraw();
    
    Message checkFailure();
    Message checkSuccess();

    Message run();

    void initMove();
    void initSelectHero();
    void initSelectAbility();
    Message selectHero(int id);
    Message selectAbility(int id);

    int CPUSelectAbility();
    int CPUSelectTarget();
};