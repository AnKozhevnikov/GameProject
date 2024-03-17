#include "AbilityManager.h"

AbilityManager::AbilityManager(std::shared_ptr<Ability> newAbility, std::shared_ptr<AbilityDrawer> newDrawer) : ability(newAbility), drawer(newDrawer), selected(false) {}

AbilityManager::AbilityManager(const AbilityManager &other): ability(other.ability), drawer(other.drawer), selected(other.selected) {}

AbilityManager& AbilityManager::operator=(const AbilityManager &other) {
    if (this != &other) {
        ability = other.ability;
        drawer = other.drawer;
        selected = other.selected;
    }
    return *this;
}

bool AbilityManager::isSelected() const {
    return selected;
}

void AbilityManager::select(bool flag) {
    selected = flag;
    drawer->SelectAbility(flag);
}