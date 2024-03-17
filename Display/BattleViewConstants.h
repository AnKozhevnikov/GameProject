#pragma once
#include "constants.h"

namespace BattleViewConstants {
    const int lengthBetweenHeroes = 5;
    const int HeroLength = 14;
    const int HeroHeight = 14;
    const int BoxHeight = HeroHeight + 4; //Size of Hero sprite + 4 lines for hp, dmg, attention, initiative
    const int PlayerHeroesX = 40;
    const int EnemyHeroesY = 2;

    const constexpr int PlayerHeroesY = constants::LinesInGraphixWindow - HeroLength - 7;

    const int AbilityX = 3;
    const int AbilityY = constants::LinesInGraphixWindow - BoxHeight - 3;

    const int AbilityLength = 35;
    const int AbilityHeight = 6;

    const int AbilityIconHeight = 6;
    const int AbilityIconLength = 10;

    const int AbilityTextLength = AbilityLength - AbilityIconLength - 1;

}