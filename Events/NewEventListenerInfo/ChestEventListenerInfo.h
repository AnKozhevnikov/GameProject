#include "NewEventListenerInfo.h"

class ChestEventListenerInfo : public NewEventListenerInfo {
public:
    ChestEventListenerInfo() : NewEventListenerInfo() {
        eventType = "chest";
    };
    ChestEventListenerInfo(int parent, bool freeze) : NewEventListenerInfo(parent, freeze) {
        eventType = "chest";
    };
    ~ChestEventListenerInfo() {};
};