#include "BattleEventListener.h"
#include "NewEventListenerInfo.h"
#include "BattleViewManager.h"
#include "Display.h"
#include "BattleSamples.h"
#include <random>
#include <ctime>

BattleEventListener::BattleEventListener(const int newId, const int parent, const GameData *data, Binder *binder, std::vector<Hero> enemies) : EventListener(newId, parent, data, binder) {
    this->enemies = enemies;
    
    this->data.set_is_game_over(parentData->get_is_game_over());
    this->data.set_heroes(parentData->get_heroes());
    this->data.set_inventory(parentData->get_inventory());

    Display display;
    display.ClearGraphixWindow();
    display.SendEvent(WindowEvent(WindowEvent::INFO, "The battle has begun!"));

    for (int i=0; i<data->get_heroes_ptr()->size(); i++) {
        if (data->get_heroes_ptr()->at(i).get_name() != "void") {
            we.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(data->get_heroes_ptr()->at(i)), BattleViewManager::CreateHero(std::make_shared<Hero>(this->data.get_heroes_ptr()->at(i)), 1, i), 1));
            we[i]->drawer->SetName(data->get_heroes_ptr()->at(i).get_name());
            we[i]->drawer->SetHp(data->get_heroes_ptr()->at(i).get_hp(), data->get_heroes_ptr()->at(i).get_maxHp());
            we[i]->drawer->SetDmg(data->get_heroes_ptr()->at(i).get_dmg());
            we[i]->drawer->SetAttention(data->get_heroes_ptr()->at(i).get_initiative());
            we[i]->drawer->SetInitiative(data->get_heroes_ptr()->at(i).get_initiative());
        }
        else we.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(data->get_heroes_ptr()->at(i)), nullptr, 0));
    }

    for (int i=0; i<enemies.size(); i++) {
        if (enemies[i].get_name() != "void") {
            they.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(enemies[i]), BattleViewManager::CreateHero(std::make_shared<Hero>(enemies[i]), 0, i), 0));
            they[i]->drawer->SetName(enemies[i].get_name());
            they[i]->drawer->SetHp(enemies[i].get_hp(), enemies[i].get_maxHp());
            they[i]->drawer->SetDmg(enemies[i].get_dmg());
            they[i]->drawer->SetAttention(enemies[i].get_initiative());
            they[i]->drawer->SetInitiative(enemies[i].get_initiative());
        }
        else they.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(enemies[i]), nullptr, 1));
    }

    currentInOrder = 0;
    for (int i=0; i<we.size(); i++) {
        if (we[i]->hero->get_name() != "void") {
            order.push_back(we[i]);
        }
    }
    for (int i=0; i<they.size(); i++) {
        if (they[i]->hero->get_name() != "void") {
            order.push_back(they[i]);
        }
    }
    sort(order.begin(), order.end(), [](std::shared_ptr<HeroManager> a, std::shared_ptr<HeroManager> b) {return a->hero->get_initiative() > b->hero->get_initiative();});

    abilities.resize(3);

    initMove();
    bind(-1, &BattleEventListener::checkEnd, this, "check end");
    bind(-1, &BattleEventListener::run, this, "run");
}

void BattleEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();

    for (int i=0; i<we.size(); i++) {
        if (we[i]->hero->get_name() != "void") {
            BattleViewManager::RemoveHero(i, 1);
            we[i]->drawer = nullptr;
            we[i]->drawer = BattleViewManager::CreateHero(std::make_shared<Hero>(*we[i]->hero), 1, i);
            we[i]->drawer->SetName(we[i]->hero->get_name());
            we[i]->drawer->SetHp(we[i]->hero->get_hp(), we[i]->hero->get_maxHp());
            we[i]->drawer->SetDmg(we[i]->hero->get_dmg());
            we[i]->drawer->SetAttention(we[i]->hero->get_initiative());
            we[i]->drawer->SetInitiative(we[i]->hero->get_initiative());
            we[i]->drawer->ApplyEffect(VisualEffect::STUN, we[i]->isStunned());
            we[i]->drawer->ApplyEffect(VisualEffect::BURN, we[i]->isBurned());
            we[i]->drawer->ApplyEffect(VisualEffect::SELECT_AS_SOURCE, we[i]->isSelectedAsSource());
            we[i]->drawer->ApplyEffect(VisualEffect::SELECT_AS_TARGET, we[i]->isSelectedAsTarget());
            we[i]->drawer->ApplyEffect(VisualEffect::DEAD, we[i]->isDead());
        }
    }

    for (int i=0; i<they.size(); i++) {
        if (they[i]->hero->get_name() != "void") {
            BattleViewManager::RemoveHero(i, 0);
            they[i]->drawer = nullptr;
            they[i]->drawer = BattleViewManager::CreateHero(std::make_shared<Hero>(*they[i]->hero), 0, i);
            they[i]->drawer->SetName(they[i]->hero->get_name());
            they[i]->drawer->SetHp(they[i]->hero->get_hp(), they[i]->hero->get_maxHp());
            they[i]->drawer->SetDmg(they[i]->hero->get_dmg());
            they[i]->drawer->SetAttention(they[i]->hero->get_initiative());
            they[i]->drawer->SetInitiative(they[i]->hero->get_initiative());
            they[i]->drawer->ApplyEffect(VisualEffect::STUN, they[i]->isStunned());
            they[i]->drawer->ApplyEffect(VisualEffect::BURN, they[i]->isBurned());
            they[i]->drawer->ApplyEffect(VisualEffect::SELECT_AS_SOURCE, they[i]->isSelectedAsSource());
            they[i]->drawer->ApplyEffect(VisualEffect::SELECT_AS_TARGET, they[i]->isSelectedAsTarget());
            they[i]->drawer->ApplyEffect(VisualEffect::DEAD, they[i]->isDead());
        }
    }

    for (int i=0; i<abilities.size(); i++) {
        if (abilities[i] != nullptr) {
            BattleViewManager::RemoveAbility(i);
            abilities[i] = nullptr;
            abilities[i] = std::make_shared<AbilityManager>(abilities[i]->ability, BattleViewManager::CreateAbility(abilities[i]->ability, i));
        }
    }
}

void BattleEventListener::initMove() {
    if (order[currentInOrder]->isDead()) {
        currentInOrder++;
        if (currentInOrder == order.size()) {
            currentInOrder = 0;
        }
        initMove();
        return;
    }

    step = 0;
    teamSelect = false;
    heroSelected = -1;
    abilitySelected = -1;
    order[currentInOrder]->selectAsSource(true);
    initSelectAbility();
}

void BattleEventListener::initSelectAbility() {
    if (order[currentInOrder]->isStunned()) {
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::ACTION, order[currentInOrder]->hero->get_name() + " is stunned and cannot move"));
        step = 3;
        return;
    }
    if (order[currentInOrder]->team) {
        abilitySelected = 0;
        
        for (int i=0; i < abilities.size(); i++) {
            abilities[i] = std::make_shared<AbilityManager>(std::make_shared<Ability>(order[currentInOrder]->hero->get_abilities_ptr()->at(i)), BattleViewManager::CreateAbility(std::make_shared<Ability>(order[currentInOrder]->hero->get_abilities_ptr()->at(i)), i));
        }
        abilities[0]->select(true);

        bind('w', &BattleEventListener::selectAbility, this, "move selector to the up", -1);
        bind('s', &BattleEventListener::selectAbility, this, "move selector to the down", 1);
        bind(10, &BattleEventListener::selectAbility, this, "confirm selection", 0);
    }
    else {
        abilitySelected = CPUSelectAbility();
        teamSelect = !(order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_team() ^ order[currentInOrder]->team);
        step=1;
        initSelectHero();
    }
}

Message BattleEventListener::selectAbility(int id) {
    if (id == 0) {
        if (order[currentInOrder]->team) {
            unbind(&BattleEventListener::selectAbility, this, "move selector to the up", -1);
            unbind(&BattleEventListener::selectAbility, this, "move selector to the down", 1);
            unbind(&BattleEventListener::selectAbility, this, "confirm selection", 0);
        }
        step = 1;
        teamSelect = !(order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_team() ^ order[currentInOrder]->team);
        initSelectHero();
    }
    else {
        abilities[abilitySelected]->select(false);

        abilitySelected += id;
        abilitySelected = (abilitySelected + 3)%3;
        
        abilities[abilitySelected]->select(true);
    }
    return Message();
}

void BattleEventListener::initSelectHero() {
    if (order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_multitarget() == 1) {
        heroSelected = 0;
        step = 2;
        initAbilityApply();
    }
    else if (order[currentInOrder]->team) {
        if (teamSelect) {
            for (int i=0; i<we.size(); i++) {
                if (we[i]->hero->get_name() != "void" && !we[i]->isDead()) {
                    heroSelected = i;
                    we[i]->selectAsTarget(true);
                    break;
                }
            }
        }
        else {
            for (int i=0; i<we.size(); i++) {
                if (they[i]->hero->get_name() != "void" && !they[i]->isDead()) {
                    heroSelected = i;
                    they[i]->selectAsTarget(true);
                    break;
                }
            }
        }
        bind('a', &BattleEventListener::selectHero, this, "move selector to the left", -1);
        bind('d', &BattleEventListener::selectHero, this, "move selector to the right", 1);
        bind(10, &BattleEventListener::selectHero, this, "confirm selection", 0);
    }
    else {
        heroSelected = CPUSelectTarget();
        step = 2;
        initAbilityApply();
    }
}

Message BattleEventListener::selectHero(int id) {
    if (id == 0) {
        if (order[currentInOrder]->team) {
            unbind(&BattleEventListener::selectHero, this, "move selector to the left", -1);
            unbind(&BattleEventListener::selectHero, this, "move selector to the right", 1);
            unbind(&BattleEventListener::selectHero, this, "confirm selection", 0);
        }
        if (teamSelect) {
            we[heroSelected]->selectAsTarget(false);
        }
        else {
            they[heroSelected]->selectAsTarget(false);
        }
        step = 2;
        initAbilityApply();
    }
    else {
        if (teamSelect) {
            we[heroSelected]->selectAsTarget(false);
            if (we[heroSelected]->isSelectedAsSource()) order[currentInOrder]->selectAsSource(true);

            heroSelected += id;
            heroSelected = (heroSelected + we.size())%we.size();
            while (we[heroSelected]->hero->get_name() == "void" || we[heroSelected]->isDead()) {
                heroSelected += id;
                heroSelected = (heroSelected + we.size())%we.size();
            }
            we[heroSelected]->selectAsTarget(true);
        }
        else {
            they[heroSelected]->selectAsTarget(false);
            if (they[heroSelected]->isSelectedAsSource()) order[currentInOrder]->selectAsSource(true);

            heroSelected += id;
            heroSelected = (heroSelected + they.size())%they.size();
            while (they[heroSelected]->hero->get_name() == "void" || they[heroSelected]->isDead()) {
                heroSelected += id;
                heroSelected = (heroSelected + they.size())%they.size();
            }
            they[heroSelected]->selectAsTarget(true);
        }
    }
    return Message();
}   

void BattleEventListener::initAbilityApply() {
    std::vector<std::shared_ptr<HeroManager>> toMoveAt;
    if (teamSelect) {
        if (order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_multitarget() == 1) {
            toMoveAt = std::vector<std::shared_ptr<HeroManager>>{we[0], we[1], we[2]};
        }
        else {
            toMoveAt = std::vector<std::shared_ptr<HeroManager>>{we[heroSelected]};
        }
    }
    else {
        if (order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_multitarget() == 1) {
            toMoveAt = std::vector<std::shared_ptr<HeroManager>>{they[0], they[1], they[2]};
        }
        else {
            toMoveAt = std::vector<std::shared_ptr<HeroManager>>{they[heroSelected]};
        }
    }

    order[currentInOrder]->applyMove(abilitySelected, toMoveAt);
    step=3;
}

bool BattleEventListener::updateAnimation() {
    bool flag=true;
    for (int i=0; i<order.size(); i++) {
        flag &= order[i]->drawer->UpdateAnimations();
    }
    return flag;
}

Message BattleEventListener::run() {
    bool flag = updateAnimation();
    if (step == 3 && flag) {
        abilities = std::vector<std::shared_ptr<AbilityManager>>(3);
        BattleViewManager::ClearAllAbilities();
        order[currentInOrder]->selectAsSource(false);
        
        order[currentInOrder]->applyStatus();

        currentInOrder++;
        if (currentInOrder == order.size()) {
            currentInOrder = 0;
        }
        initMove();
    }
    return Message();
}

int BattleEventListener::CPUSelectAbility() {
    std::mt19937 gen(time(0));
    return gen()%3;
}

int BattleEventListener::CPUSelectTarget() {
    std::mt19937 gen(time(0));
    int ret;
    while (true) {
        if (teamSelect) {
            ret = gen()%we.size();
            if (we[ret]->hero->get_name() != "void" && !we[ret]->isDead()) {
                return ret;
            }
        }
        else {
            ret = gen()%they.size();
            if (they[ret]->hero->get_name() != "void" && !they[ret]->isDead()) {
                return ret;
            }
        }
    }
}

bool BattleEventListener::checkFailure() {
    for (int i=0; i<we.size(); i++) {
        if (we[i]->hero->get_name() != "void" && !we[i]->isDead()) {
            return false;
        }
    }
    return true;
}

bool BattleEventListener::checkSuccess() {
    for (int i=0; i<they.size(); i++) {
        if (they[i]->hero->get_name() != "void" && !they[i]->isDead()) {
            return false;
        }
    }
    return true;
}

void BattleEventListener::clear() {
    BattleViewManager::ClearAllHeroes();
    BattleViewManager::ClearAllAbilities();
}

Message BattleEventListener::checkEnd() {
    bool fail = checkFailure();
    bool win = checkSuccess();

    std::vector<Hero> heroes;
    if (fail || win) {
        for (int i=0; i<we.size(); i++) {
            if (!we[i]->dead) heroes.push_back(*we[i]->hero);
            else heroes.push_back(SampleHeroes::voidHero);
        }
        data.set_heroes(heroes);
    }

    if (fail) {
        data.set_is_game_over(true);
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::INFO, "You've lost"));
        clear();
        return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
    }
    else if (win) {
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::INFO, "You've won"));
        clear();
        return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
    }
    return Message();
}