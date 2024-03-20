#include "NewEventListenerInfo.h"

class TrapEventListenerInfo : public NewEventListenerInfo
{
public:
    TrapEventListenerInfo() : NewEventListenerInfo() {
        eventType = "trap";
    };
    TrapEventListenerInfo(int parent, bool freeze) : NewEventListenerInfo(parent, freeze) {
        eventType = "trap";
    };
    ~TrapEventListenerInfo() {};
};