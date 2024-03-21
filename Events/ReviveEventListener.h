#pragma once

#include "EventListener.h"
#include "HeroManager.h"
#include "GameData.h"
#include "AbilityManager.h"
#include <vector>
#include "BattleViewManager.h"
#include "ItemManager.h"

class ReviveEventListener: public EventListener {
public:
    ReviveEventListener() : EventListener() {};
    ReviveEventListener(const int newId, const int parent, const GameData *data, Binder *binder, int price);
private:
    int price;
    std::vector<std::shared_ptr<HeroManager>> we;
    std::shared_ptr<HeroManager> dead;
    std::shared_ptr<ItemDrawer> itemDrawer;

    void redraw();
    Message addToTeam(int pos);
    Message applyChoice(int id);
    Message selectorCase(int id);
    Message Kill();
};