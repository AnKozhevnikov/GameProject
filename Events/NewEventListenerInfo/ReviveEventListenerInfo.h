#include "NewEventListenerInfo.h"

class ReviveEventListenerInfo : public NewEventListenerInfo
{
public:
    ReviveEventListenerInfo() : NewEventListenerInfo() {
        eventType = "revive";
    };
    ReviveEventListenerInfo(int parent, bool freeze) : NewEventListenerInfo(parent, freeze) {
        eventType = "revive";
    };
    ~ReviveEventListenerInfo() {};
};