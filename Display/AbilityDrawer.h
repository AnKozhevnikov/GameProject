#ifndef GAMEPROJECT_ABILITYDRAWER_H
#define GAMEPROJECT_ABILITYDRAWER_H
#include "Ability.h"

class AbilityDrawer {
    AbilityDrawer(const Ability &ability, int x, int y);
    ~AbilityDrawer();

    void SelectAbility();
};


#endif //GAMEPROJECT_ABILITYDRAWER_H
