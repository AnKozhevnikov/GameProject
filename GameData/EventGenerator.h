#pragma once

#include <memory>
#include "NewEventListenerInfo.h"
#include "TrapEventListenerInfo.h"
#include "ChestEventListenerInfo.h"
#include "AltarEventListenerInfo.h"
#include "ReviveEventListenerInfo.h"
#include "NpcEventListenerInfo.h"
#include "BattleEventListenerInfo.h"
#include "BattleSamples.h"
#include "Randomizer.h"

namespace EventGenerator {
static std::shared_ptr<NewEventListenerInfo> generateEasyBattle(int id, int depth, int maxHp, int maxDmg) {
    std::vector<Hero> heroes = Randomizer::getRandomSquad(depth, maxHp, maxDmg, 3, false, 0);
    return std::make_shared<BattleEventListenerInfo>(id, true, heroes);
}

static std::shared_ptr<NewEventListenerInfo> generateMediumBattle(int id, int depth, int maxHp, int maxDmg) {
    std::vector<Hero> heroes = Randomizer::getRandomSquad(depth, maxHp, maxDmg, 3, false, 1);
    return std::make_shared<BattleEventListenerInfo>(id, true, heroes);
}

static std::shared_ptr<NewEventListenerInfo> generateBossBattle(int id, int depth, int maxHp, int maxDmg) {
    std::vector<Hero> heroes = Randomizer::getRandomSquad(depth, maxHp, maxDmg, 3, false, 2);
    return std::make_shared<BattleEventListenerInfo>(id, true, heroes);
}

static std::shared_ptr<NewEventListenerInfo> generateTrap(int id, int depth) {
    return std::make_shared<TrapEventListenerInfo>(id, true);
}

static std::shared_ptr<NewEventListenerInfo> generateChest(int id, int depth) {
    return std::make_shared<ChestEventListenerInfo>(id, true);
}

static std::shared_ptr<NewEventListenerInfo> generateAltar(int id, int depth) {
    return std::make_shared<AltarEventListenerInfo>(id, true);
}

static std::shared_ptr<NewEventListenerInfo> generateRevive(int id, int depth) {
    int price = Randomizer::getRandom(50) + 75;
    return std::make_shared<ReviveEventListenerInfo>(id, true, price);
}

static std::shared_ptr<NewEventListenerInfo> generateNpc(int id, int depth) {
    int price = Randomizer::getRandom(50) + 75;
    Hero hero = SampleHeroes::warrior;
    return std::make_shared<NpcEventListenerInfo>(id, true, hero, price);
}
}