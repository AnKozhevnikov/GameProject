#pragma once
#include <memory>
#include "Item.h"

typedef std::shared_ptr<Item> PItem;


class ItemDrawer {
private:
    int x, y;
    PItem pitem;
public:
    explicit ItemDrawer(PItem pitem, int x, int y);
    void Select(bool state);
    ~ItemDrawer();
};


