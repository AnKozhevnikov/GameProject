#include "EventListener.h"
#include "HeroManager.h"
#include "GameData.h"
#include "AbilityManager.h"
#include "ReviveEventListener.h"
#include <vector>
#include "Display.h"
#include "Drawer.h"

ReviveEventListener::ReviveEventListener(const int newId, const int parent, const GameData *data, Binder *binder, int price) : EventListener(newId, parent, data, binder) {
    this->data.set_heroes(parentData->get_heroes());
    this->data.set_inventory(parentData->get_inventory());
    this->data.set_dead(parentData->get_dead());

    this->price = price;

    Display display;
    display.ClearGraphixWindow();
    display.SendEvent(WindowEvent(WindowEvent::INFO, "You've encountered a priest"));

    std::vector<std::pair<int, int>> positions = {{47, 28}, {66, 28}, {85, 28}};
    for (int i = 0; i< data->get_heroes_ptr()->size(); i++) {
        if (data->get_heroes_ptr()->at(i).get_name() != "void") {
            we.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(data->get_heroes_ptr()->at(i)), std::make_shared<HeroDrawer>(std::make_shared<Hero>(data->get_heroes_ptr()->at(i)), positions[i].first, positions[i].second), 1));
            we[i]->drawer->SetName(data->get_heroes_ptr()->at(i).get_name());
            we[i]->drawer->SetHp(data->get_heroes_ptr()->at(i).get_hp(), data->get_heroes_ptr()->at(i).get_maxHp());
            we[i]->drawer->SetDmg(data->get_heroes_ptr()->at(i).get_dmg());
            we[i]->drawer->SetAttention(data->get_heroes_ptr()->at(i).get_initiative());
            we[i]->drawer->SetInitiative(data->get_heroes_ptr()->at(i).get_initiative());
        }
        else we.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(data->get_heroes_ptr()->at(i)), nullptr, 0));
    }

    this->itemDrawer = std::make_shared<ItemDrawer>(this->data.get_inventory_ptr()->get_gold_ptr(), 0, 0);
    display.DrawSprite(Drawer::getSprite("revive"), 45, 5);

    if (this->data.get_dead().get_name() == "void") {
        display.SendEvent(WindowEvent(WindowEvent::INFO, "You don't have any dead heroes"));
        bind(10, &ReviveEventListener::Kill, this, "Exit");
    } else {
        display.SendEvent(WindowEvent(WindowEvent::INFO, "Would you like to revive a hero for " + std::to_string(price) + " gold?"));
        bind('y', &ReviveEventListener::applyChoice, this, "I would like to revive a hero", 1);
        bind('n', &ReviveEventListener::applyChoice, this, "Let him die peacefully", 0);

        this->dead = std::make_shared<HeroManager>(data->get_dead_ptr(), std::make_shared<HeroDrawer>(data->get_dead_ptr(), 15, 28), 0);
        this->dead->drawer->SetName(data->get_dead_ptr()->get_name());
        this->dead->drawer->SetHp(data->get_dead_ptr()->get_hp(), data->get_dead_ptr()->get_maxHp());
        this->dead->drawer->SetDmg(data->get_dead_ptr()->get_dmg());
        this->dead->drawer->SetAttention(data->get_dead_ptr()->get_initiative());
        this->dead->drawer->SetInitiative(data->get_dead_ptr()->get_initiative());
    }
}

void ReviveEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();
    std::vector<std::pair<int, int>> positions = {{47, 28}, {66, 28}, {85, 28}};
    for (int i=0; i<we.size(); i++) {
        if (we[i]->hero->get_name() != "void") {
            we[i]->drawer = nullptr;
            we[i]->drawer = std::make_shared<HeroDrawer>(we[i]->hero, positions[i].first, positions[i].second);
            we[i]->drawer->SetName(we[i]->hero->get_name());
            we[i]->drawer->SetHp(we[i]->hero->get_hp(), we[i]->hero->get_maxHp());
            we[i]->drawer->SetDmg(we[i]->hero->get_dmg());
            we[i]->drawer->SetAttention(we[i]->hero->get_initiative());
            we[i]->drawer->SetInitiative(we[i]->hero->get_initiative());
        }
    }

    this->dead->drawer = nullptr;
    this->dead = std::make_shared<HeroManager>(dead->hero, std::make_shared<HeroDrawer>(dead->hero, 15, 28), 0);
    this->dead->drawer->SetName(dead->hero->get_name());
    this->dead->drawer->SetHp(dead->hero->get_hp(), dead->hero->get_maxHp());
    this->dead->drawer->SetDmg(dead->hero->get_dmg());
    this->dead->drawer->SetAttention(dead->hero->get_initiative());
    this->dead->drawer->SetInitiative(dead->hero->get_initiative());

    display.DrawSprite(Drawer::getSprite("revive"), 45, 5);
}

Message ReviveEventListener::addToTeam(int pos) {
    if (pos >= 0 && pos < we.size()) {
        we[pos]->hero = std::make_shared<Hero>(data.get_dead());
        std::vector<Hero> updatedHeroes;
        for (const auto& heroManager : we) {
            updatedHeroes.push_back(*(heroManager->hero));
        }
        data.set_heroes(updatedHeroes);
    }
    return Kill();
}

Message ReviveEventListener::applyChoice(int id) {
    if (id) {
        if (price <= data.get_inventory().get_gold().get_amount()) {
            data.get_inventory_ptr()->get_gold_ptr()->set_amount(data.get_inventory().get_gold().get_amount() - price);
            this->itemDrawer = nullptr;
            this->itemDrawer = std::make_shared<ItemDrawer>(this->data.get_inventory_ptr()->get_gold_ptr(), 0, 0);
            int pos = -1;
            for (int i = 0; i < we.size(); i++) {
                if (we[i]->hero->get_name() == "void") {
                    pos = i;
                    break;
                }
            }
            if (pos != -1) {
                return addToTeam(pos);
            } else {
                Display display;
                display.SendEvent(WindowEvent(WindowEvent::INFO, "Choose which hero you want to change"));
                we[0]->selectAsSource(1);
                unbind(&ReviveEventListener::applyChoice, this, "I would like to revive a hero", 1);
                unbind(&ReviveEventListener::applyChoice, this, "Let him die peacefully", 0);
                bind('a', &ReviveEventListener::selectorCase, this, "Move selector to the left", -1);
                bind('d', &ReviveEventListener::selectorCase, this, "Move selector to the right", 1);
                bind(10, &ReviveEventListener::selectorCase, this, "Confirm", 0);
            }
        } else {
            Display display;
            display.SendEvent(WindowEvent(WindowEvent::INFO, "You don't have enough gold to revive this hero!"));
            unbind(&ReviveEventListener::applyChoice, this, "I would like to revive a hero", 1);
            unbind(&ReviveEventListener::applyChoice, this, "Let him die peacefully", 0);
            bind(10, &ReviveEventListener::Kill, this, "Exit");
        }
    } else {
        return Kill();
    }
    return Message();
}

Message ReviveEventListener::selectorCase(int id) {
    if (id == 1) {
        if (we[2]->isSelectedAsSource()) {
            Display display;
            display.SendEvent(WindowEvent(WindowEvent::INFO, "Can't move selector to the right"));
        } else {
            if (we[0]->isSelectedAsSource()) {
                we[0]->selectAsSource(0);
                we[1]->selectAsSource(1);
            } else {
                we[1]->selectAsSource(0);
                we[2]->selectAsSource(1);
            }
        }
    } else if (id == 0) {
        int pos;
        for (int i = 0; i < we.size(); ++i) {
            if (we[i]->isSelectedAsSource()) {
                pos = i;
            }
        }
        return addToTeam(pos);
    } else {
        if (we[0]->isSelectedAsSource()) {
            Display display;
            display.SendEvent(WindowEvent(WindowEvent::INFO, "Can't move selector to the right"));
        } else {
            if (we[1]->isSelectedAsSource()) {
                we[1]->selectAsSource(0);
                we[0]->selectAsSource(1);
            } else {
                we[2]->selectAsSource(0);
                we[1]->selectAsSource(1);
            }
        }
    }
    return Message();
}

Message ReviveEventListener::Kill() {
    return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
}