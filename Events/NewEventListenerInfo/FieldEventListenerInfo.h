#include "NewEventListenerInfo.h"

class FieldEventListenerInfo : public NewEventListenerInfo
{
public:
    FieldEventListenerInfo() : NewEventListenerInfo() {
        eventType = "field";
    };
    FieldEventListenerInfo(int parent, bool freeze) : NewEventListenerInfo(parent, freeze) {
        eventType = "field";
    };
    ~FieldEventListenerInfo() {};
};