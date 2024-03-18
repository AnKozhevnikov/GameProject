#pragma once

#include "NewEventListenerInfo.h"

class MainMenuEventListenerInfo : public NewEventListenerInfo
{
public:
    MainMenuEventListenerInfo(int parent, bool freeze) {
        this->parent = parent;
        this->freeze = freeze;
        eventType = "MainMenu";
    };
};