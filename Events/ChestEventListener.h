#pragma once

#include "EventListener.h"

class ChestEventListener : public EventListener {
public:
    ChestEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    void init();
    //void draw();
    Message open();

};