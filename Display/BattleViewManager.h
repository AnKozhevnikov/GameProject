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

namespace BattleViewManager {
    PHeroDrawer CreateHero(PHero phero, bool team, int pos = -1);
    void RemoveHero(int id, bool team);
    void ClearAllHeroes();
    PHeroDrawer GetHeroDrawer(int id, bool team);

    PAbilityDrawer CreateAbility(PAbility pability, int pos = -1);
    void RemoveAbility(int id);
    void ClearAllAbilities();
    PAbilityDrawer GetAbilityDrawer(int id);
};