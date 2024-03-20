#include "NewEventListenerInfo.h"

class NpcEventListenerInfo : public NewEventListenerInfo
{
public:
    NpcEventListenerInfo() : NewEventListenerInfo() {
        eventType = "npc";
    };
    NpcEventListenerInfo(int parent, bool freeze, Hero hero, int price) : NewEventListenerInfo(parent, freeze) {
        eventType = "npc";
        this->hero = hero;
        this->price = price;
    };
    ~NpcEventListenerInfo() {};

    Hero hero;
    int price;
};