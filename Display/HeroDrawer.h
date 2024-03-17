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
    SELECT
};

class HeroDrawer {
    int x, y;
public:
    explicit HeroDrawer(PHero phero, int x = -1, int y = -1);
    void SetHp(int cur_hp, int max_hp);
    void SetDmg(int value);
    void SetAttention(int value);
    void SetInitiative(int value);
    void SetName(const std::string &name);
    void SetChoice(bool state);
    void ApplyEffect(VisualEffect effect, bool state) const;
    ~HeroDrawer();
};