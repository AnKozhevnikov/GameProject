#pragma once
#include <vector>
#include <array>
#include <memory>
#include "HeroDrawer.h"
#include "constants.h"
#include "AbilityDrawer.h"
#include <stdexcept>

typedef std::shared_ptr<HeroDrawer> PHeroDrawer;
typedef std::shared_ptr<Hero> PHero;

typedef std::shared_ptr<AbilityDrawer> PAbilityDrawer;
typedef std::shared_ptr<Ability> PAbility;


static std::pair<int, int> get_pos(int idx, bool team);

namespace BattleViewManager {
    const int lengthBetweenHeroes = 5;
    const int HeroLength = 14;
    const int HeroHeight = 14;
    const int BoxHeight = HeroHeight + 4;
    const int PlayerHeroesX = 40;
    const int EnemyHeroesY = 5;

    const constexpr int PlayerHeroesY = constants::LinesInGraphixWindow - HeroLength - EnemyHeroesY;

    const int AbilityX = 3;
    const int AbilityY = constants::LinesInGraphixWindow - BoxHeight;

    const int AbilityBoxHeight = 6;
    const int AbilityBoxLength = 12;

    PHeroDrawer CreateHero(PHero phero, bool team, int pos = -1);
    void RemoveHero(int id, bool team);
    void ClearAllHeroes();
    PHeroDrawer GetHeroDrawer(int id, bool team);

    PAbilityDrawer CreateAbility(PAbility pability, int pos = -1);
    void RemoveAbility(int id);
    void ClearAllAbilities();
    PAbilityDrawer GetAbilityDrawer(int id);
};