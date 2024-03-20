#include "NewEventListenerInfo.h"

class NpcEventListenerInfo : public NewEventListenerInfo
{
public:
    NpcEventListenerInfo() : NewEventListenerInfo() {
        eventType = "npc";
    };
    NpcEventListenerInfo(int parent, bool freeze) : NewEventListenerInfo(parent, freeze) {
        eventType = "npc";
    };
    ~NpcEventListenerInfo() {};
};