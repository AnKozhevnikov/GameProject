#pragma once

#include "EventListener.h"
#include "HeroManager.h"
#include "GameData.h"
#include "AbilityManager.h"
#include <vector>
#include "BattleViewManager.h"
#include "ItemManager.h"

class NpcEncounterEventListener: public EventListener {
public:
    NpcEncounterEventListener() : EventListener() {};
    NpcEncounterEventListener(const int newId, const int parent, const GameData *data, Binder *binder, Hero NewHero, int price);
private:
    int price;
    Hero NewHero;
    std::shared_ptr<HeroManager> they;
    std::vector<std::shared_ptr<HeroManager>> we;
    std::vector<std::shared_ptr<HeroManager>> order;
    int currentInOrder;
    int heroSelected;
    std::shared_ptr<ItemDrawer> itemDrawer;

    void redraw();
    Message addToTeam(int pos);
    Message applyChoice(int id);
    Message selectorCase(int id);
    Message Kill();

};