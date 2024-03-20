#include "HeroManager.h"
#include "GameData.h"
#include "BattleSamples.h"

HeroManager::HeroManager(std::shared_ptr<Hero> newHero, std::shared_ptr<HeroDrawer> newDrawer, bool newTeam) {
    hero = newHero;
    drawer = newDrawer;
    team = newTeam;
    burn = 0;
    stun = 0;
    selectedAsSource = false;
    selectedAsTarget = false;
    dead = false;
}

HeroManager::HeroManager(const HeroManager &other) {
    hero = other.hero;
    drawer = other.drawer;
    team = other.team;
    burn = other.burn;
    stun = other.stun;
    selectedAsSource = other.selectedAsSource;
    selectedAsTarget = other.selectedAsTarget;
    dead = other.dead;
}

HeroManager& HeroManager::operator=(const HeroManager &other) {
    hero = other.hero;
    drawer = other.drawer;
    team = other.team;
    burn = other.burn;
    stun = other.stun;
    selectedAsSource = other.selectedAsSource;
    selectedAsTarget = other.selectedAsTarget;
    dead = other.dead;
    return *this;
}

bool HeroManager::isStunned() const {
    return stun > 0;
}

bool HeroManager::isBurned() const {
    return burn > 0;
}

bool HeroManager::isDead() const {
    return dead;
}

bool HeroManager::isSelectedAsSource() const {
    return selectedAsSource;
}

bool HeroManager::isSelectedAsTarget() const {
    return selectedAsTarget;
}

void HeroManager::selectAsSource(bool flag) {
    selectedAsSource = flag;
    drawer->ApplyEffect(VisualEffect::SELECT_AS_SOURCE, flag);
}

void HeroManager::selectAsTarget(bool flag) {
    selectedAsTarget = flag;
    drawer->ApplyEffect(VisualEffect::SELECT_AS_TARGET, flag);
}

void HeroManager::applyStatus() {
    if (hero->get_name() == "void") return;
    if (burn > 0) {
        applyDamage(hero->get_maxHp() / 10);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " gets damage from burning"));
        burn--;
        if (burn == 0) {
            drawer->ApplyEffect(VisualEffect::BURN, false);
            display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " is no longer burning"));
        }
        else {
            display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " will burn for " + std::to_string(burn) + " more turns"));
        }
    }
    if (stun > 0) {
        Display display;
        stun--;
        if (stun == 0) {
            drawer->ApplyEffect(VisualEffect::STUN, false);
            display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " is no longer stunned"));
        }
        else {
            display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " will be stunned for " + std::to_string(stun) + " more turns"));
        }
    }

    checkIfKilled();
}

void HeroManager::setBurn(int cnt) {
    if (hero->get_name() == "void") return;
    burn = cnt;
    if (burn > 0) { 
        drawer->ApplyEffect(VisualEffect::BURN, true);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " will burn for " + std::to_string(burn) + " turns"));
    }
    else {
        drawer->ApplyEffect(VisualEffect::BURN, false);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " is healed from burning"));
    }
}

void HeroManager::setStun(int cnt) {
    if (hero->get_name() == "void") return;
    stun = cnt;
    if (stun > 0) { 
        drawer->ApplyEffect(VisualEffect::STUN, true);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " will be stunned for " + std::to_string(stun) + " turns"));
    }
    else {
        drawer->ApplyEffect(VisualEffect::STUN, false);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " is healed from stunning"));
    }
}

void HeroManager::applyDamage(int dmg) {
    if (hero->get_name() == "void") return;
    if (dmg > hero->get_hp()) dmg = hero->get_hp();
    hero->set_hp(hero->get_hp() - dmg);
    drawer->ApplyEffect(VisualEffect::DAMAGE, true);
    drawer->SetHp(hero->get_hp(), hero->get_maxHp());
    checkIfKilled();
}

void HeroManager::applyHeal(double heal) {
    if (hero->get_name() == "void") return;
    if (heal * hero->get_maxHp() > hero->get_maxHp() - hero->get_hp()) heal = (double)(hero->get_maxHp() - hero->get_hp())/hero->get_maxHp();
    hero->set_hp(hero->get_hp() + hero->get_maxHp() * heal);
    drawer->ApplyEffect(VisualEffect::HEAL, true);
    drawer->SetHp(hero->get_hp(), hero->get_maxHp());
}

void HeroManager::applyStatusHeal(bool state) {
    if (hero->get_name() == "void") return;
    if (state) {
        setBurn(0);
        setStun(0);
        drawer->ApplyEffect(VisualEffect::HEAL_STATUS_EFFECTS, true);
    }
}

void HeroManager::checkIfKilled() {
    if (hero->get_hp() <= 0) {
        dead = true;
        drawer->ApplyEffect(VisualEffect::DEAD, true);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, hero->get_name() + " is dead"));
    }
}

void HeroManager::applyMove(int ability, std::vector<std::shared_ptr<HeroManager>> toMoveAt) {
    for (int i=0; i<toMoveAt.size(); i++) {
        Ability curAbility = hero->get_abilities_ptr()->at(ability);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, "Ability " + curAbility.get_name() + " used on " + toMoveAt[i]->hero->get_name() + " by " + hero->get_name()));

        if (curAbility.get_damage() > 0) {
            toMoveAt[i]->applyDamage(hero->get_dmg() * curAbility.get_damage());
        }

        if (curAbility.get_heal() > 0) {
            toMoveAt[i]->applyHeal(curAbility.get_heal());
        }

        if (curAbility.get_heal_status() > 0) {
            toMoveAt[i]->applyStatusHeal(true);
        }

        if (curAbility.get_burn() > 0) {
            toMoveAt[i]->setBurn(curAbility.get_burn());
        }

        if (curAbility.get_stun() > 0) {
            toMoveAt[i]->setStun(curAbility.get_stun());
        }
    }
}

void HeroManager::applyPotion(std::shared_ptr<Ability> potion) {
    if (hero->get_name() == "void") return;
    Display display;
    display.SendEvent(WindowEvent(WindowEvent::ACTION, "Potion " + potion->get_name() + " used on " + hero->get_name()));

    if (potion->get_damage() > 0) {
        applyDamage(potion->get_damage() * hero->get_maxHp());
    }

    if (potion->get_heal() > 0) {
        applyHeal(potion->get_heal());
    }

    if (potion->get_heal_status() > 0) {
        applyStatusHeal(potion->get_heal_status());
    }

    if (potion->get_burn() > 0) {
        setBurn(potion->get_burn());
    }

    if (potion->get_stun() > 0) {
        setStun(potion->get_stun());
    }
}