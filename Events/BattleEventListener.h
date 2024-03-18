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
    std::vector<std::shared_ptr<HeroManager>> we;
    std::vector<std::shared_ptr<HeroManager>> they;
    int currentInOrder;
    std::vector<std::shared_ptr<HeroManager>> order;
    std::vector<std::shared_ptr<AbilityManager>> abilities;

    int step; // 0 - select ability, 1 - select target, 2 - apply ability, 3 - finished
    bool teamSelect;
    int heroSelected;
    int abilitySelected;

    void redraw();
    
    bool checkFailure();
    bool checkSuccess();
    Message checkEnd();
    void clear();

    Message run();

    void initMove();
    void initSelectHero();
    void initSelectAbility();
    void initAbilityApply();
    Message selectHero(int id);
    Message selectAbility(int id);
    bool updateAnimation();

    int CPUSelectAbility();
    int CPUSelectTarget();
};