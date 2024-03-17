#ifndef GAMEPROJECT_ABILITYDRAWER_H
#define GAMEPROJECT_ABILITYDRAWER_H
#include "Ability.h"

class AbilityDrawer {
private:
    int x, y;
    Ability ability;
public:
    AbilityDrawer(const Ability &ability, int x, int y);
    ~AbilityDrawer();
    [[nodiscard]] Ability GetAbility() const;
    void SelectAbility(bool state);
};


#endif //GAMEPROJECT_ABILITYDRAWER_H