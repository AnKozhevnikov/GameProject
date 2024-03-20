#include "NewEventListenerInfo.h"

class ReviveEventListenerInfo : public NewEventListenerInfo
{
public:
    ReviveEventListenerInfo() : NewEventListenerInfo() {
        eventType = "revive";
    };
    ReviveEventListenerInfo(int parent, bool freeze, int price) : NewEventListenerInfo(parent, freeze) {
        eventType = "revive";
        this->price = price;
    };
    ~ReviveEventListenerInfo() {};

    int price;
};