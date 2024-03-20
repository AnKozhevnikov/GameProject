#pragma once

#include "NewEventListenerInfo.h"

class MainMenuEventListenerInfo : public NewEventListenerInfo
{
public:
    MainMenuEventListenerInfo() : NewEventListenerInfo() {
        eventType = "MainMenu";
    };
    MainMenuEventListenerInfo(int parent, bool freeze) {
        this->parent = parent;
        this->freeze = freeze;
        eventType = "MainMenu";
    };
};