#pragma once

#include "Drawer.h"

class FieldEventDrawer : public Drawer {
public:
    //public methods for drawing Field on screen
    void draw_field(const Field& field);
};