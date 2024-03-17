#pragma once

#include <vector>
#include <array>
#include <memory>
#include "Hero.h"

class HeroDrawer;

typedef std::shared_ptr<HeroDrawer> PHeroDrawer;
typedef std::shared_ptr<Hero> PHero;

enum class VisualEffect {
    BURN,
    STUN,
    HEAL,
    DEAD,
    SELECT_AS_SOURCE,
    SELECT_AS_TARGET,
    DAMAGE
};

class HeroDrawer {
private:
    int x, y;
    void SetChoice(bool state, short clr) const;
public:
    explicit HeroDrawer(PHero phero, int x = -1, int y = -1);
    void SetHp(int cur_hp, int max_hp);
    void SetDmg(int value);
    void SetAttention(int value);
    void SetInitiative(int value);
    void SetName(const std::string &name);
    void ApplyEffect(VisualEffect effect, bool state) const;
    ~HeroDrawer();
};