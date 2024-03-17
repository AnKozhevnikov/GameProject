#pragma once
#include <vector>
#include <array>
#include <memory>
#include "HeroDrawer.h"
#include "constants.h"
#include <stdexcept>

typedef std::shared_ptr<HeroDrawer> PHeroDrawer;
typedef std::shared_ptr<Hero> PHero;

static std::pair<int, int> get_pos(int idx, bool team);

namespace BattleViewManager {
    static inline std::array<std::shared_ptr<HeroDrawer> , 3> playerHeroes = {nullptr, nullptr, nullptr};
    static inline std::array<std::shared_ptr<HeroDrawer> , 3> enemyHeroes = {nullptr, nullptr, nullptr};
    const int lengthBetweenHeroes = 5;
    const int HeroLength = 14;
    const int HeroHeight = 14;
    const int BoxHeight = 18;
    const int PlayerHeroesX = 40;
    const int EnemyHeroesY = 5;
    const constexpr int PlayerHeroesY = constants::LinesInGraphixWindow - HeroLength - EnemyHeroesY;

    static PHeroDrawer CreateHero(PHero phero, bool team, int pos) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? enemyHeroes : playerHeroes;
        if(pos != -1) {
            if(heroes[pos] != nullptr) {
                throw std::runtime_error("Enemy hero already exists at this position");
            }
            int x, y;
            std::tie(x, y) = get_pos(pos, team);
            heroes[pos] = std::make_shared<HeroDrawer>(phero, x, y);
            return heroes[pos];
        }
        for(int idx = 0; idx < 3; ++idx) {
            if(heroes[idx] == nullptr) {
                int x, y;
                std::tie(x, y) = get_pos(idx, team);
                heroes[idx] = std::make_shared<HeroDrawer>(phero, x, y);
                return heroes[idx];
            }
        }
        throw std::runtime_error("No space for hero");
    }
    static void RemoveHero(int id, bool team) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? enemyHeroes : playerHeroes;
        if(heroes[id] == nullptr) {
            throw std::runtime_error("No hero to remove");
        }
        heroes[id] = nullptr;
    }
    static void ClearAllHeroes() {
        for(int i = 0; i < 3; ++i) {
            RemoveHero(i, false);
            RemoveHero(i, true);
        }
    }
    static PHeroDrawer GetHeroDrawer(int id, bool team) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? enemyHeroes : playerHeroes;
        if(heroes[id] == nullptr) {
            throw std::runtime_error("No hero to get");
        }
        return heroes[id];
    }
};

static std::pair<int, int> get_pos(int idx, bool team) {
    if(team) { //Enemy team
        return std::make_pair(BattleViewManager::lengthBetweenHeroes * (idx + 1) +
                              BattleViewManager::HeroLength * idx, BattleViewManager::EnemyHeroesY);
    }
    else{
        return std::make_pair(BattleViewManager::PlayerHeroesX + BattleViewManager::lengthBetweenHeroes * (idx + 1) +
                              BattleViewManager::HeroLength * idx, BattleViewManager::PlayerHeroesY);
    }
}
