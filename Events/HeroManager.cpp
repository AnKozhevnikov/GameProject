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
}

HeroManager::HeroManager(const HeroManager &other) {
    hero = other.hero;
    drawer = other.drawer;
    team = other.team;
    burn = other.burn;
    stun = other.stun;
    selectedAsSource = other.selectedAsSource;
    selectedAsTarget = other.selectedAsTarget;
}

HeroManager& HeroManager::operator=(const HeroManager &other) {
    hero = other.hero;
    drawer = other.drawer;
    team = other.team;
    burn = other.burn;
    stun = other.stun;
    selectedAsSource = other.selectedAsSource;
    selectedAsTarget = other.selectedAsTarget;
    return *this;
}

bool HeroManager::isStunned() const {
    return stun > 0;
}

bool HeroManager::isBurned() const {
    return burn > 0;
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
        checkIfKilled();
        burn--;
    }
    if (stun > 0) {
        stun--;
    }
}

void HeroManager::setBurn(int cnt) {
    if (hero->get_name() == "void") return;
    burn = cnt;
    //do something with drawer
}

void HeroManager::setStun(int cnt) {
    if (hero->get_name() == "void") return;
    stun = cnt;
    //do something with drawer
}

void HeroManager::applyDamage(int dmg) {
    if (hero->get_name() == "void") return;
    hero->set_hp(hero->get_hp() - dmg);
    //do something with drawer
    checkIfKilled();
}

void HeroManager::applyHeal(double heal) {
    if (hero->get_name() == "void") return;
    hero->set_hp(hero->get_hp() + hero->get_maxHp() * heal);
    //do something with drawer
}

void HeroManager::applyStatusHeal() {
    if (hero->get_name() == "void") return;
    setBurn(0);
    setStun(0);
}

void HeroManager::checkIfKilled() {
    if (hero->get_hp() <= 0) {
        Hero deadHero = SampleHeroes::voidHero;
        hero = std::make_shared<Hero>(deadHero);
        //do something with drawer
    }
}

void HeroManager::applyMove(int ability, std::vector<std::shared_ptr<HeroManager>> toMoveAt) {
    
}