#pragma once

#include "EventListener.h"

class AltarEventListener : public EventListener {
public:
    AltarEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    void init();
    //void draw();
    Message destroy();
    Message use();

};