#pragma once

#include "Ability.h"
#include "AbilityDrawer.h"
#include <memory>

class AbilityManager
{
public:
    std::shared_ptr<Ability> ability;
    std::shared_ptr<AbilityDrawer> drawer;

    bool selected;

    AbilityManager(std::shared_ptr<Ability> newAbility, std::shared_ptr<AbilityDrawer> newDrawer);
    AbilityManager(const AbilityManager &other);
    AbilityManager& operator=(const AbilityManager &other);

    bool isSelected() const;
    void select(bool flag);
};