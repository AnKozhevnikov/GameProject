#include "AltarEventListener.h"
#include "Display.h"
#include "bitmap_image.hpp"
#include "Drawer.h"
#include "Randomizer.h"

AltarEventListener::AltarEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_field(parentData->get_field());
    data.set_heroes(parentData->get_heroes());
    data.set_inventory(parentData->get_inventory());
    init();
    //redraw();
}

void AltarEventListener::init() {
    Display display;
    bind('e', &AltarEventListener::use, this, "pray to the God", 1);
    bind('r', &AltarEventListener::destroy, this, "destroy the chansel", 1);
}

Message AltarEventListener::use() {
    std::vector<Hero> heroes = data.get_heroes();
    int dice1 = Randomizer::getRandom(100);
    if (dice1 == 42) {
        int slave = Randomizer::getRandom(3);
        int master = (slave + 1) % 3;
        heroes[slave].set_name(heroes[slave].get_name() + ", the Cursed");
        heroes[master].set_name(heroes[slave].get_name() + ", the Blessed");
        
        heroes[master].set_maxHp(heroes[master].get_maxHp() + heroes[slave].get_maxHp());
        heroes[master].set_hp(heroes[master].get_hp() + heroes[slave].get_hp());
        heroes[master].set_dmg(heroes[master].get_dmg() + heroes[slave].get_dmg());
        heroes[master].set_initiative(heroes[master].get_initiative() + heroes[slave].get_initiative());
        heroes[master].set_attention(heroes[master].get_attention() + heroes[slave].get_attention());

        heroes[slave].set_maxHp(1);
        heroes[slave].set_hp(1);
        heroes[slave].set_dmg(1);
        heroes[slave].set_initiative(1);
        heroes[slave].set_attention(1);

        Display display;
        display.SendEvent(WindowEvent(WindowEvent::INFO, "God is the judge"));
    
    } else {
        int dice2 = Randomizer::getRandom(4);
        if (dice2 == 0) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_maxHp(heroes[i].get_maxHp() + (int) round(heroes[i].get_maxHp()/(Randomizer::getRandom(4) + 1)));
            }
        } else if (dice2 == 1) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_dmg(heroes[i].get_dmg() + (int) round(heroes[i].get_dmg()/(Randomizer::getRandom(4) + 1)));
            }
        } else if (dice2 == 2) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_initiative(heroes[i].get_initiative() + (int) round(heroes[i].get_initiative()/(Randomizer::getRandom(4) + 1)));
            }
        } else if (dice2 == 3) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_attention(heroes[i].get_attention() + (int) round(heroes[i].get_attention()/(Randomizer::getRandom(4) + 1)));
            }
        }
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::INFO, "You were blessed to bring the light further")); 
    }   
    data.set_heroes(heroes);
    return Message(data, NewEventListenerInfo(), true, id);
}

Message AltarEventListener::destroy() {
    std::vector<Hero> heroes = data.get_heroes();
    
    if (Randomizer::getRandom(4) == 2) {
        int dice2 = Randomizer::getRandom(4);
        if (dice2 == 0) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_maxHp(heroes[i].get_maxHp()*2);
            }
        } else if (dice2 == 1) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_dmg(heroes[i].get_dmg()*2);
            }
        } else if (dice2 == 2) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_initiative(heroes[i].get_initiative()*2);
            }
        } else if (dice2 == 3) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_attention(heroes[i].get_attention()*2);
            }
        }
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::INFO, "You were blessed for destruction of heresy")); 
    } else {
        int dice2 = Randomizer::getRandom(4);
        if (dice2 == 0) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_maxHp(heroes[i].get_maxHp()/2);
                heroes[i].set_hp(heroes[i].get_maxHp());
            }
        } else if (dice2 == 1) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_dmg(heroes[i].get_dmg()/2);
            }
        } else if (dice2 == 2) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_initiative(heroes[i].get_initiative()/2);
            }
        } else if (dice2 == 3) {
            for (int i = 0; i < 3; i++) {
                heroes[i].set_attention(heroes[i].get_attention()/2);
            }
        }
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::INFO, "You were cursed for sacriledge")); 
        data.set_heroes(heroes);
        return Message(data, NewEventListenerInfo(), true, id);
    } 
}

