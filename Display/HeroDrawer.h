#pragma once

#include <vector>
#include <array>
#include <memory>
#include "Hero.h"
#include <chrono>

class HeroDrawer;

typedef std::shared_ptr<HeroDrawer> PHeroDrawer;
typedef std::shared_ptr<Hero> PHero;

using std::vector;

enum VisualEffect {
    BURN,
    STUN,
    HEAL,
    DEAD,
    SELECT_AS_SOURCE,
    SELECT_AS_TARGET,
    DAMAGE,
    LAST [[maybe_unused]]  //NOT FOR USE
};
typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> timeSymbol;
typedef vector<timeSymbol> timevec;

class HeroDrawer {
private:
    int x, y;
    vector<vector<unsigned>> my_sprite;
    std::array<bool, VisualEffect::LAST> is_running;
    timevec start;
    void SetChoice(bool state, short clr) const;
    bool ApplyHeal(bool state);
    bool ApplyDamage(bool state);

    void ApplyBurn(int state); //1 - enable 0 - disable -1 - do nothing
    void ApplyStun(int state);
    void ApplyDead(int state);
public:
    explicit HeroDrawer(PHero phero, int x = -1, int y = -1);
    void SetHp(int cur_hp, int max_hp);
    void SetDmg(int value);
    void SetAttention(int value);
    void SetInitiative(int value);
    void SetName(const std::string &name);
    void ApplyEffect(VisualEffect effect, bool state);
    bool UpdateAnimations(); //True if all animations are done
    ~HeroDrawer();
};