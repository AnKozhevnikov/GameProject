#include "TrapEventListener.h"
#include "Display.h"
#include "Drawer.h"
#include "Randomizer.h"
#include "BattleSamples.h"

TrapEventListener::TrapEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_heroes(parentData->get_heroes());
    data.set_field(parentData->get_field());

    std::vector<std::pair<int, int>> positions = {{25, 28}, {45, 28}, {65, 28}};
    for (int i = 0; i< data.get_heroes_ptr()->size(); i++) {
        if (data.get_heroes_ptr()->at(i).get_name() != "void") {
            we.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(data.get_heroes_ptr()->at(i)), std::make_shared<HeroDrawer>(std::make_shared<Hero>(data.get_heroes_ptr()->at(i)), positions[i].first, positions[i].second), 1));
            we[i]->drawer->SetName(data.get_heroes_ptr()->at(i).get_name());
            we[i]->drawer->SetHp(data.get_heroes_ptr()->at(i).get_hp(), data.get_heroes_ptr()->at(i).get_maxHp());
            we[i]->drawer->SetDmg(data.get_heroes_ptr()->at(i).get_dmg());
            we[i]->drawer->SetAttention(data.get_heroes_ptr()->at(i).get_initiative());
            we[i]->drawer->SetInitiative(data.get_heroes_ptr()->at(i).get_initiative());
        }
        else we.push_back(std::make_shared<HeroManager>(std::make_shared<Hero>(data.get_heroes_ptr()->at(i)), nullptr, 0));
    }

    init();
    //redraw();
};

Message TrapEventListener::init() {
    bind('e', &TrapEventListener::exit, this, "continue");
    bind(-1, &TrapEventListener::update, this, "update animations");

    Display display;
    display.SendEvent(WindowEvent(WindowEvent::ACTION, "It's a trap!"));

    for (int i = 0; i < 3; i++) {
        if (we[i]->hero->get_initiative() < Randomizer::getRandom(10)) {
            we[i]->applyDamage(we[i]->hero->get_maxHp()*2/10);

        }
    }
    display.DrawSprite(Drawer::getSprite("trap"), 23, 0);
     
    std::vector<Hero> heroes;
    for (int i=0; i<3; i++) {
        if (!we[i]->isDead()) {
            heroes.push_back(*we[i]->hero);
        }
        else {
            heroes.push_back(SampleHeroes::voidHero);
        }
    }
    data.set_heroes(heroes);

    return Message(data, std::make_shared<NewEventListenerInfo>(), false, id);
}

Message TrapEventListener::exit() {
    return Message(GameData(), std::make_shared<NewEventListenerInfo>(), true, id);
}

Message TrapEventListener::update() {
    for (int i=0; i<3; i++) {
        if (we[i]->drawer != nullptr) we[i]->drawer->UpdateAnimations();
    }
    return Message();
}