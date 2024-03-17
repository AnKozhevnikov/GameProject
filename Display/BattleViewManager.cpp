#include "BattleViewManager.h"

static std::pair<int, int> get_pos(int idx, bool team);

namespace BattleViewManager {
    std::array<std::shared_ptr<HeroDrawer>, 3> playerHeroes = {nullptr, nullptr, nullptr};
    std::array<std::shared_ptr<HeroDrawer>, 3> enemyHeroes = {nullptr, nullptr, nullptr};
    PHeroDrawer CreateHero(PHero phero, bool team, int pos) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? playerHeroes : enemyHeroes;
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
    void ClearAllHeroes() {
        for(int i = 0; i < 3; ++i) {
            RemoveHero(i, false);
            RemoveHero(i, true);
        }
    }
    void RemoveHero(int id, bool team) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? playerHeroes : enemyHeroes;
        if(heroes[id] == nullptr) {
            throw std::runtime_error("No hero to remove");
        }
        heroes[id] = nullptr;
    }
    PHeroDrawer GetHeroDrawer(int id, bool team) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? playerHeroes : enemyHeroes;
        if(heroes[id] == nullptr) {
            throw std::runtime_error("No hero to get");
        }
        return heroes[id];
    }

    std::array<std::shared_ptr<AbilityDrawer>, 3> abilities = {nullptr, nullptr, nullptr};
    PAbilityDrawer CreateAbility(PAbility pability, int pos) {
        if(pos != -1) {
            if(abilities[pos] != nullptr) {
                throw std::runtime_error("Ability already exists at this position");
            }
            int x = AbilityX, y = AbilityY + pos * AbilityBoxHeight;
            abilities[pos] = std::make_shared<AbilityDrawer>(*pability, x, y);
            return abilities[pos];
        }
        for(int idx = 0; idx < 3; ++idx) {
            if(abilities[idx] == nullptr) {
                int x = AbilityX, y = AbilityY + pos * AbilityBoxHeight;
                abilities[idx] = std::make_shared<AbilityDrawer>(*pability, x, y);
                return abilities[idx];
            }
        }
        throw std::runtime_error("No space for ability");
    }

    void ClearAllAbilities() {
        for(int i = 0; i < 3; ++i) {
            RemoveAbility(i);
        }
    }

    void RemoveAbility(int id) {
        abilities[id] = nullptr;
    }

    PAbilityDrawer GetAbilityDrawer(int id) {
        if(abilities[id] == nullptr) {
            throw std::runtime_error("No ability to get");
        }
        return abilities[id];
    }
}

static std::pair<int, int> get_pos(int idx, bool team) {
    if(!team) { //Enemy team
        return std::make_pair(BattleViewManager::lengthBetweenHeroes * (idx + 1) +
                              BattleViewManager::HeroLength * idx, BattleViewManager::EnemyHeroesY);
    }
    else{
        return std::make_pair(BattleViewManager::PlayerHeroesX + BattleViewManager::lengthBetweenHeroes * (idx + 1) +
                              BattleViewManager::HeroLength * idx, BattleViewManager::PlayerHeroesY);
    }
}