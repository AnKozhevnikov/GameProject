#include "BattleEventListener.h"
#include "NewEventListenerInfo.h"
#include "BattleViewManager.h"
#include "Display.h"
#include <random>
#include <ctime>

BattleEventListener::BattleEventListener(const int newId, const int parent, const GameData *data, Binder *binder, std::vector<Hero> enemies) : EventListener(newId, parent, data, binder) {
    this->enemies = enemies;
    
    this->data.set_is_game_over(parentData->get_is_game_over());
    this->data.set_heroes(parentData->get_heroes());
    this->data.set_inventory(parentData->get_inventory());

    for (int i=0; i<data->get_heroes_ptr()->size(); i++) {
        if (data->get_heroes_ptr()->at(i).get_name() != "void") {
            we.push_back(HeroManager(std::make_shared<Hero>(data->get_heroes_ptr()->at(i)), BattleViewManager::CreateHero(std::make_shared<Hero>(this->data.get_heroes_ptr()->at(i)), 0, i), 0));
            //also apply everything
        }
        else
            we.push_back(HeroManager(std::make_shared<Hero>(data->get_heroes_ptr()->at(i)), nullptr, 0));
    }

    for (int i=0; i<enemies.size(); i++) {
        if (enemies[i].get_name() != "void") {
            they.push_back(HeroManager(std::make_shared<Hero>(enemies[i]), BattleViewManager::CreateHero(std::make_shared<Hero>(enemies[i]), 1, i), 1));
            //also apply everything
        }
        else
            they.push_back(HeroManager(std::make_shared<Hero>(enemies[i]), nullptr, 1));
    }

    currentInOrder = 0;
    for (int i=0; i<we.size(); i++) {
        if (we[i].hero->get_name() != "void") {
            order.push_back(std::make_shared<HeroManager>(we[i]));
        }
    }
    for (int i=0; i<they.size(); i++) {
        if (they[i].hero->get_name() != "void") {
            order.push_back(std::make_shared<HeroManager>(they[i]));
        }
    }
    sort(order.begin(), order.end(), [](std::shared_ptr<HeroManager> a, std::shared_ptr<HeroManager> b) {return a->hero->get_initiative() > b->hero->get_initiative();});

    initMove();
    bind(-1, &BattleEventListener::run, this, "run");
}

void BattleEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();

    for (int i=0; i<we.size(); i++) {
        if (we[i].hero->get_name() != "void") {
            BattleViewManager::RemoveHero(i, 0);
            we[i].drawer = nullptr;
            we[i].drawer = BattleViewManager::CreateHero(std::make_shared<Hero>(*we[i].hero), 0, i);
            //also apply everything
        }
    }

    for (int i=0; i<they.size(); i++) {
        if (they[i].hero->get_name() != "void") {
            BattleViewManager::RemoveHero(i, 1);
            they[i].drawer = nullptr;
            they[i].drawer = BattleViewManager::CreateHero(std::make_shared<Hero>(*they[i].hero), 1, i);
            //also apply everything
        }
    }
}

void BattleEventListener::initMove() {
    moveFinished = false;
    step = 0;
    teamSelect = false;
    heroSelected = -1;
    abilitySelected = -1;
    //order[currentInOrder]->select(true);
    initSelectAbility();
}

void BattleEventListener::initSelectAbility() {
    if (order[currentInOrder]->isStunned()) {
        moveFinished = true;
        return;
    }
    if (order[currentInOrder]->team) {
        abilitySelected = 0;
        //do something with ability manager
        bind('a', &BattleEventListener::selectAbility, this, "move selector to the left", -1);
        bind('d', &BattleEventListener::selectAbility, this, "move selector to the right", 1);
        bind(10, &BattleEventListener::selectAbility, this, "confirm selection", 0);
    }
    else {
        abilitySelected = CPUSelectAbility();
        step=1;
        initSelectHero();
    }
}

Message BattleEventListener::selectAbility(int id) {
    if (id == 0) {
        if (order[currentInOrder]->team) {
            unbind(&BattleEventListener::selectAbility, this, "move selector to the left", -1);
            unbind(&BattleEventListener::selectAbility, this, "move selector to the right", 1);
            unbind(&BattleEventListener::selectAbility, this, "confirm selection", 0);
        }
        step = 1;
        teamSelect = order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_team() ^ order[currentInOrder]->team;
        initSelectHero();
    }
    else {
        abilitySelected += id;
        abilitySelected = (abilitySelected + 3)%3;
        //do something with ability manager
    }
    return Message();
}

void BattleEventListener::initSelectHero() {
    if (order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_multitarget() == 1) {
        heroSelected = 0;
        moveFinished = true;
    }
    else if (order[currentInOrder]->team) {
        if (teamSelect) {
            for (int i=0; i<we.size(); i++) {
                if (we[i].hero->get_name() != "void") {
                    heroSelected = i;
                    we[i].select(true);
                    break;
                }
            }
        }
        else {
            for (int i=0; i<we.size(); i++) {
                if (they[i].hero->get_name() != "void") {
                    heroSelected = i;
                    they[i].select(true);
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
        moveFinished = true;
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
            we[heroSelected].select(false);
        }
        else {
            they[heroSelected].select(false);
        }
        moveFinished = true;
    }
    else {
        if (teamSelect) {
            we[heroSelected].select(false);
            heroSelected += id;
            heroSelected = (heroSelected + we.size())%we.size();
            while (we[heroSelected].hero->get_name() == "void") {
                heroSelected += id;
                heroSelected = (heroSelected + we.size())%we.size();
            }
            we[heroSelected].select(true);
        }
        else {
            they[heroSelected].select(false);
            heroSelected += id;
            heroSelected = (heroSelected + they.size())%they.size();
            while (they[heroSelected].hero->get_name() == "void") {
                heroSelected += id;
                heroSelected = (heroSelected + they.size())%they.size();
            }
            they[heroSelected].select(true);
        }
    }
    return Message();
}   

Message BattleEventListener::run() {
    if (moveFinished) {
        if (order[currentInOrder]->hero->get_abilities_ptr()->at(abilitySelected).get_multitarget() == 0) {
            if (order[currentInOrder]->team) {
                order[currentInOrder]->applyMove(abilitySelected, std::vector<HeroManager*>{&they[heroSelected]});
            }
            else {
                order[currentInOrder]->applyMove(abilitySelected, std::vector<HeroManager*>{&we[heroSelected]});
            }
        }
        else {
            if (order[currentInOrder]->team) {
                order[currentInOrder]->applyMove(abilitySelected, std::vector<HeroManager*>{&they[0], &they[1], &they[2]});
            }
            else {
                order[currentInOrder]->applyMove(abilitySelected, std::vector<HeroManager*>{&we[0], &we[1], &we[2]});
            }
        }
        
        currentInOrder++;
        if (currentInOrder == order.size()) {
            for (int i=0; i<order.size(); i++) {
                order[i]->applyStatus();
            }
            currentInOrder = 0;
        }
        moveFinished = false;
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
            if (we[ret].hero->get_name() != "void") {
                return ret;
            }
        }
        else {
            ret = gen()%they.size();
            if (they[ret].hero->get_name() != "void") {
                return ret;
            }
        }
    }
}

Message BattleEventListener::checkFailure() {
    for (int i=0; i<we.size(); i++) {
        if (we[i].hero->get_name() != "void") {
            return Message();
        }
    }
    data.set_is_game_over(true);
    return Message(data, NewEventListenerInfo(), true, id);
}

Message BattleEventListener::checkSuccess() {
    for (int i=0; i<they.size(); i++) {
        if (they[i].hero->get_name() != "void") {
            return Message();
        }
    }
    return Message(data, NewEventListenerInfo(), true, id);
}