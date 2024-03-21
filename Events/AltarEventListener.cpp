#include "AltarEventListener.h"
#include "Display.h"
#include "Drawer.h"
#include "Randomizer.h"

AltarEventListener::AltarEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_heroes(parentData->get_heroes());
    std::vector<std::pair<int, int>> positions = {{25, 28}, {45, 28}, {65, 28}};
    for (int i=0; i < 3; i++) {
        std::shared_ptr<Hero> hero = std::make_shared<Hero>(data.get_heroes()[i]);
        heroes.push_back(std::make_shared<HeroManager>(hero, std::make_shared<HeroDrawer>(hero, positions[i].first, positions[i].second), true));
    }
    altarStatus = "nonactive";
    init();
    redraw();

    Display display;
    display.SendEvent(WindowEvent(WindowEvent::INFO, "You're standing in front of an altar"));
}

void AltarEventListener::init() {
    Display display;
    bind('e', &AltarEventListener::use, this, "pray to the God");
    bind('r', &AltarEventListener::destroy, this, "destroy the sanctuary");
    bind(-1, &AltarEventListener::update, this, "update animations");
}

Message AltarEventListener::use() {
    altarStatus = "active";
    redraw();
    int level = 1;
    int dice2 = Randomizer::getRandom(2);
    if (dice2 == 0) {
        for (int i = 0; i < 3; i++) {
            heroes[i]->hero->set_maxHp(heroes[i]->hero->get_maxHp() + (int) round(2*level + heroes[i]->hero->get_maxHp()/(Randomizer::getRandom(4) + 3)));
        }
    } else if (dice2 == 1) {
        for (int i = 0; i < 3; i++) {
            heroes[i]->hero->set_dmg(heroes[i]->hero->get_dmg() + (int) round(2*level + heroes[i]->hero->get_dmg()/(Randomizer::getRandom(4) + 3)));
        }
    }

    redraw();
    Display display;
    display.SendEvent(WindowEvent(WindowEvent::REPLY, "You were blessed to bring the light further")); 

    for (int i=0; i<3; i++) {
        heroes[i]->applyIllumination(true);
    }
       
    data.set_heroes({*heroes[0]->hero, *heroes[1]->hero, *heroes[2]->hero});

    unbind(&AltarEventListener::use, this, "pray to the God");
    unbind(&AltarEventListener::destroy, this, "destroy the sanctuary");
    bind('e', &AltarEventListener::exit, this, "continue");    

    return Message(GameData(), std::make_shared<NewEventListenerInfo>(), false, id);
}

Message AltarEventListener::destroy() {
    altarStatus = "destroyed";
    redraw();
    int level = 1;
    if (Randomizer::getRandom(level=1) * Randomizer::getRandom(level+1) >= 2*level) {
        int dice2 = Randomizer::getRandom(2);
        if (dice2 == 0) {
            for (int i = 0; i < 3; i++) {
                heroes[i]->hero->set_maxHp(heroes[i]->hero->get_maxHp()*2);
            }
        } else if (dice2 == 1) {
            for (int i = 0; i < 3; i++) {
                heroes[i]->hero->set_dmg(heroes[i]->hero->get_dmg()*2);
            }
        }

        for (int i=0; i<3; i++) {
            heroes[i]->applyIllumination(true);
        }

        Display display;
        display.SendEvent(WindowEvent(WindowEvent::REPLY, "You were blessed for exterminating the heresy")); 
    } else {
        int dice2 = Randomizer::getRandom(2);
        if (dice2 == 0) {
            for (int i = 0; i < 3; i++) {
                if (heroes[i]->hero->get_maxHp() > 1)
                    heroes[i]->hero->set_maxHp(heroes[i]->hero->get_maxHp()/2);
                heroes[i]->hero->set_hp(min(heroes[i]->hero->get_maxHp(), heroes[i]->hero->get_hp()));
            }
            redraw();
            for (int i=0; i<3; i++) {
                heroes[i]->applyDamage(0);
            }
        } else if (dice2 == 1) {
            for (int i = 0; i < 3; i++) {
                if (heroes[i]->hero->get_dmg() > 1)
                    heroes[i]->hero->set_dmg(heroes[i]->hero->get_dmg()/2);
            }
            redraw();
            for (int i=0; i<3; i++) {
                heroes[i]->applyDamage(0);
            }
        }
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::REPLY, "You were cursed for sacriledge")); 
    }
    data.set_heroes({*heroes[0]->hero, *heroes[1]->hero, *heroes[2]->hero});

    unbind(&AltarEventListener::use, this, "pray to the God");
    unbind(&AltarEventListener::destroy, this, "destroy the sanctuary");
    bind('e', &AltarEventListener::exit, this, "continue");

    return Message(GameData(), std::make_shared<NewEventListenerInfo>(), false, id);
}

Message AltarEventListener::exit() {
    return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
}

void AltarEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();
    if (altarStatus == "nonactive") {
        display.DrawSprite(Drawer::getSprite("altar_off"), 23, 0);
    } else if (altarStatus == "active") {
        display.DrawSprite(Drawer::getSprite("altar"), 23, 0);
    } else if (altarStatus == "destroyed") {
        display.DrawSprite(Drawer::getSprite("altar_destroy"), 23, 0);
    }

    std::vector<std::pair<int, int>> positions = {{25, 28}, {45, 28}, {65, 28}};
    for (int i=0; i<3; i++) {
        if (heroes[i]->hero->get_name() != "void") {
            heroes[i]->drawer = nullptr;
            heroes[i]->drawer = std::make_shared<HeroDrawer>(heroes[i]->hero, positions[i].first, positions[i].second);
            heroes[i]->drawer->SetName(heroes[i]->hero->get_name());
            heroes[i]->drawer->SetHp(heroes[i]->hero->get_hp(), heroes[i]->hero->get_maxHp());
            heroes[i]->drawer->SetDmg(heroes[i]->hero->get_dmg());
            heroes[i]->drawer->SetAttention(heroes[i]->hero->get_initiative());
            heroes[i]->drawer->SetInitiative(heroes[i]->hero->get_initiative());
        }
    }
}

Message AltarEventListener::update() {
    for (int i=0; i<3; i++) {
        heroes[i]->drawer->UpdateAnimations();
    }
    return Message();
}