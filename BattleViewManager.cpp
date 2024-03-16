#include <stdexcept>
#include <memory>
#include "BattleViewManager.h"
#include "Display.h"
#include "constants.h"

static std::pair<int, int> get_pos(int idx, bool team);
class HeroManager;

typedef std::shared_ptr<HeroDrawer> PHeroDrawer;
typedef std::shared_ptr<HeroManager> PHeroManager;
using std::vector;



namespace BattleViewManager {
    std::array<std::shared_ptr<HeroDrawer> , 3> playerHeroes = {nullptr, nullptr, nullptr};
    std::array<std::shared_ptr<HeroDrawer> , 3> enemyHeroes = {nullptr, nullptr, nullptr};
    std::array<std::shared_ptr<HeroManager> , 3> playerHeroManagers = {nullptr, nullptr, nullptr};
    std::array<std::shared_ptr<HeroManager> , 3> enemyHeroManagers = {nullptr, nullptr, nullptr};
    const int lengthBetweenHeroes = 5;
    const int HeroLength = 14;
    const int HeroHeight = 14;
    const int BoxHeight = 18;
    const int EnemyHeroesY = 5;
    const constexpr int PlayerHeroesY = constants::LinesInGraphixWindow - HeroLength - EnemyHeroesY;

    PHeroDrawer CreateHero(PHeroManager phero, bool team, int pos) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? enemyHeroes : playerHeroes;
        std::array<std::shared_ptr<HeroManager>, 3> &heroManagers = team ? enemyHeroManagers : playerHeroManagers;
        if(pos != -1) {
            if(heroes[pos] != nullptr) {
                throw std::runtime_error("Enemy hero already exists at this position");
            }
            int x, y;
            std::tie(x, y) = get_pos(pos, team);
            heroes[pos] = std::make_shared<HeroDrawer>(phero, x, y);
            heroManagers[pos] = phero;
            return heroes[pos];
        }
        for(int idx = 0; idx < 3; ++idx) {
            if(heroes[idx] == nullptr) {
                int x, y;
                std::tie(x, y) = get_pos(idx, team);
                heroes[idx] = std::make_shared<HeroDrawer>(phero, x, y);
                heroManagers[idx] = phero;
                return heroes[idx];
            }
        }
    }
    void RemoveHero(int id, bool team) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? enemyHeroes : playerHeroes;
        if(heroes[id] == nullptr) {
            throw std::runtime_error("No hero to remove");
        }
        heroes[id] = nullptr;
    }
    void ClearAllHeroes() {
        for(int i = 0; i < 3; ++i) {
            RemoveHero(i, false);
            RemoveHero(i, true);
        }
    }
    PHeroDrawer GetHeroDrawer(int id, bool team) {
        std::array<std::shared_ptr<HeroDrawer>, 3> &heroes = team ? enemyHeroes : playerHeroes;
        if(heroes[id] == nullptr) {
            throw std::runtime_error("No hero to get");
        }
        return heroes[id];
    }
    PHeroManager GetHeroManager(int id, bool team) {
        std::array<std::shared_ptr<HeroManager>, 3> &heroes = team ? enemyHeroManagers : playerHeroManagers;
        if(heroes[id] == nullptr) {
            throw std::runtime_error("No hero to get");
        }
        return heroes[id];
    }
}

static std::pair<int, int> get_pos(int idx, bool team) {
    if(team) { //Enemy team
        return std::make_pair(BattleViewManager::lengthBetweenHeroes * (idx + 1) +
                              BattleViewManager::HeroLength * idx, BattleViewManager::EnemyHeroesY);
    }
    else{
        return std::make_pair(BattleViewManager::lengthBetweenHeroes * (idx + 1) +
                              BattleViewManager::HeroLength * idx, BattleViewManager::PlayerHeroesY);
    }
}

HeroDrawer::HeroDrawer(PHeroManager phero, int x_, int y_) {
    x = x_;
    y = y_;
    Display display;

    std::shared_ptr<std::vector<std::vector<unsigned int>>> sprite = phero->get_sprite_ptr();
    if(sprite->size() != BattleViewManager::HeroHeight) throw std::runtime_error("Invalid sprite height");
    for(const auto &line : *sprite) {
        if(line.size() > BattleViewManager::HeroLength)
            throw std::runtime_error("Invalid sprite length");
    }
    display.DrawSprite(*sprite, x, y);

    //TODO Apply Effects
}

void HeroDrawer::SetChoice(bool state) {
    Display display;
    if(state) {
        display.DrawSprite(vector<vector<unsigned>> (1, vector<unsigned> (' ' | COLOR_YELLOW | A_BLINK)), x, y + BattleViewManager::HeroHeight + 1);
    }
    else{
        ColorManager manager;
        display.DrawSprite(vector<vector<unsigned>> (1, vector<unsigned> (' ' | manager.CreateColorPair(-1, -1))), x, y + BattleViewManager::HeroHeight + 1);
    }
}

void HeroDrawer::SetHp(int cur_hp, int max_hp) {
    Display display;
    std::string hp = std::to_string(cur_hp) + "/" + std::to_string(max_hp) + " HP";
    display.DrawText(std::string(BattleViewManager::HeroLength, ' '), x, y + BattleViewManager::HeroHeight + 2); //Clear old hp
    display.DrawText(hp, x, y + BattleViewManager::HeroHeight + 2); //Draw new hp
}

void HeroDrawer::SetDmg(int value) {
    Display display;
    std::string dmg = std::to_string(value) + " DMG";
    display.DrawText(std::string(BattleViewManager::HeroLength / 2, ' '), x, y + BattleViewManager::HeroHeight + 3); //Clear old dmg
    display.DrawText(dmg, x, y + BattleViewManager::HeroHeight + 3); //Draw new dmg
}

void HeroDrawer::SetAttention(int value) {
    Display display;
    std::string attention = std::to_string(value) + " ATT";
    display.DrawText(std::string(BattleViewManager::HeroLength / 2, ' '), x + BattleViewManager::HeroLength / 2, y + BattleViewManager::HeroHeight + 3); //Clear old attention
    display.DrawText(attention, x + BattleViewManager::HeroLength / 2, y + BattleViewManager::HeroHeight + 3); //Draw new attention
}

void HeroDrawer::SetName(const std::string &name) {
    Display display;
    display.DrawText(std::string(BattleViewManager::HeroLength, ' '), x, y - 1); //Clear old name
    display.DrawText(name, x, y - 1); //Draw new name
}

void HeroDrawer::SetInitiative(int value) {
    Display display;
    std::string initiative = std::to_string(value) + " INIT";
    display.DrawText(std::string(BattleViewManager::HeroLength, ' '), x, y + BattleViewManager::HeroHeight + 4); //Clear old initiative
    display.DrawText(initiative, x, y + BattleViewManager::HeroHeight + 4); //Draw new initiative
}

HeroDrawer::~HeroDrawer() {
    Display display;
    display.DrawSprite(vector<vector<unsigned>> (BattleViewManager::HeroHeight + 5,
                vector<unsigned> (BattleViewManager::HeroLength, ' ')), x, y-1);
}

void HeroDrawer::ApplyEffect(VisualEffect effect, bool state) const {
    Display display;
    ColorManager manager;
    switch(effect) {
        //Placeholders for now, will change later
        case VisualEffect::BURN:
            display.DrawSprite(vector<vector<unsigned>> (1, vector<unsigned> (' ' | manager.CreateColorPair(COLOR_RED, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::STUN:
            display.DrawSprite(vector<vector<unsigned>> (1, vector<unsigned> (' ' | manager.CreateColorPair(COLOR_YELLOW, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::HEAL:
            display.DrawSprite(vector<vector<unsigned>> (1, vector<unsigned> (' ' | manager.CreateColorPair(COLOR_GREEN, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::DEAD:
            display.DrawSprite(vector<vector<unsigned>> (1, vector<unsigned> (' ' | manager.CreateColorPair(COLOR_BLACK, COLOR_RED))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::SELECT:
            display.DrawSprite(vector<vector<unsigned>> (1, vector<unsigned> (' ' | manager.CreateColorPair(COLOR_YELLOW, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
    }
}