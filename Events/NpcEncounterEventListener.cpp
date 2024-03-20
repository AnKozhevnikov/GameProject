#include "EventListener.h"
#include "HeroManager.h"
#include "GameData.h"
#include "AbilityManager.h"
#include "NpcEncounterEventListener.h"
#include <vector>
#include "Display.h"

NpcEncounterEventListener::NpcEncounterEventListener(const int newId, const int parent, const GameData *data, Binder *binder, Hero NewHero, int price) : EventListener(newId, parent, data, binder) {
    this->data.set_heroes(parentData->get_heroes());
    this->data.set_inventory(parentData->get_inventory());

    this->NewHero = NewHero;
    this->price = price;

    Display display;
    display.ClearGraphixWindow();
    display.SendEvent(WindowEvent(WindowEvent::INFO, "You've encountered an NPC!"));
    display.SendEvent(WindowEvent(WindowEvent::INFO, "Would you like to add a new hero to your team for " + std::to_string(price) + " gold?"));
    bind('y', &NpcEncounterEventListener::applyChoice, this, "Add new hero to team", 1);
    bind('n', &NpcEncounterEventListener::applyChoice, this, "Do not add new hero to team", 0);
    std::vector<std::pair<int, int>> positions = {{25, 28}, {45, 28}, {65, 28}};
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

    they = std::make_shared<HeroManager>(std::make_shared<Hero>(NewHero), std::make_shared<HeroDrawer>(std::make_shared<Hero>(NewHero), 45, 5), 0);
    they->drawer->SetName(NewHero.get_name());
    they->drawer->SetHp(NewHero.get_hp(), NewHero.get_maxHp());
    they->drawer->SetDmg(NewHero.get_dmg());
    they->drawer->SetAttention(NewHero.get_initiative());
    they->drawer->SetInitiative(NewHero.get_initiative());

    this->itemDrawer = std::make_shared<ItemDrawer>(this->data.get_inventory_ptr()->get_gold_ptr(), 0, 0);
}

void NpcEncounterEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();
    int x = 48, y = 28;
    for (int i=0; i<we.size(); i++) {
        if (we[i]->hero->get_name() != "void") {
            we[i]->drawer = nullptr;
            we[i]->drawer = std::make_shared<HeroDrawer>(we[i]->hero, x, y);
            we[i]->drawer->SetName(we[i]->hero->get_name());
            we[i]->drawer->SetHp(we[i]->hero->get_hp(), we[i]->hero->get_maxHp());
            we[i]->drawer->SetDmg(we[i]->hero->get_dmg());
            we[i]->drawer->SetAttention(we[i]->hero->get_initiative());
            we[i]->drawer->SetInitiative(we[i]->hero->get_initiative());
            x = x + 19;
        }
    }
    they->drawer = nullptr;
    they->drawer = std::make_shared<HeroDrawer>(they->hero, 67, 5);
    they->drawer->SetName(NewHero.get_name());
    they->drawer->SetHp(NewHero.get_hp(), NewHero.get_maxHp());
    they->drawer->SetDmg(NewHero.get_dmg());
    they->drawer->SetAttention(NewHero.get_initiative());
    they->drawer->SetInitiative(NewHero.get_initiative());

}

Message NpcEncounterEventListener::addToTeam(int pos) {
    if (id >= 0 || id < we.size()) {
        we[id]->hero = std::make_shared<Hero>(NewHero);
        std::vector<Hero> updatedHeroes;
        for (const auto& heroManager : we) {
            updatedHeroes.push_back(*(heroManager->hero));
        }
        data.set_heroes(updatedHeroes);
    }
    return Kill();
}

Message NpcEncounterEventListener::applyChoice(int id) {
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
                unbind(&NpcEncounterEventListener::applyChoice, this, "Add new hero to team", 1);
                unbind(&NpcEncounterEventListener::applyChoice, this, "Do not add new hero to team", 0); 
                bind('a', &NpcEncounterEventListener::selectorCase, this, "Move selector to the left", -1);
                bind('d', &NpcEncounterEventListener::selectorCase, this, "Move selector to the right", 1);
                bind(10, &NpcEncounterEventListener::selectorCase, this, "Confirm", 0);
            }
        } else {
            Display display;
            display.SendEvent(WindowEvent(WindowEvent::INFO, "You don't have enough gold to hire this hero!"));
            unbind(&NpcEncounterEventListener::applyChoice, this, "Add new hero to team", 1);
            unbind(&NpcEncounterEventListener::applyChoice, this, "Do not add new hero to team", 0);
            bind(10, &NpcEncounterEventListener::Kill, this, "Exit");
        }
    } else {
        return Kill();
    }
    return Message();
}

Message NpcEncounterEventListener::selectorCase(int id) {
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

Message NpcEncounterEventListener::Kill() {
    return Message(GameData(), std::make_shared<NewEventListenerInfo>(), true, id);
}