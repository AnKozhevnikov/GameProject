#include "NewEventListenerInfo.h"

class AltarEventListenerInfo : public NewEventListenerInfo
{
public:
    AltarEventListenerInfo() : NewEventListenerInfo() {
        eventType = "altar";
    };
    AltarEventListenerInfo(int parent, bool freeze) : NewEventListenerInfo(parent, freeze) {
        eventType = "altar";
    };
    ~AltarEventListenerInfo() {};
};