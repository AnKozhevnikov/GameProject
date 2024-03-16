#ifndef DISPLAY_BATTLEVIEWMANAGER_H
#define DISPLAY_BATTLEVIEWMANAGER_H

#include <vector>
#include <array>
#include <memory>
#include "Hero.h"

class HeroDrawer;
class HeroManager;

typedef std::shared_ptr<HeroDrawer> PHeroDrawer;
typedef std::shared_ptr<HeroManager> PHeroManager;

enum class VisualEffect {
    BURN,
    STUN,
    HEAL,
    DEAD,
    SELECT
};

class HeroDrawer {
    int x, y;
public:
    explicit HeroDrawer(PHeroManager phero, int x = -1, int y = -1);
    void SetHp(int cur_hp, int max_hp);
    void SetDmg(int value);
    void SetAttention(int value);
    void SetInitiative(int value);
    void SetName(const std::string &name);
    void SetChoice(bool state);
    void ApplyEffect(VisualEffect effect, bool state) const;
    ~HeroDrawer();
};

namespace BattleViewManager {
    PHeroDrawer CreateHero(PHeroManager phero, bool team, int pos = -1); //team = 0 - player, team = 1 - enemy
    void RemoveHero(int id, bool team);
    void ClearAllHeroes();
    PHeroDrawer GetHeroDrawer(int id, bool team);
    PHeroManager GetHeroManager(int id, bool team);
};


#endif //DISPLAY_BATTLEVIEWMANAGER_H
