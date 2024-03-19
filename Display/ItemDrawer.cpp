#include <vector>
#include <stdexcept>
#include "InventoryConstants.h"
#include "ItemDrawer.h"
#include "Display.h"

ItemDrawer::ItemDrawer(PItem pitem_, int x_, int y_) {
    pitem = std::move(pitem_);
    x = x_;
    y = y_;
    std::shared_ptr<std::vector<std::vector<unsigned int>>> sprite = pitem->get_sprite_ptr();
    if(sprite->size() != InventoryConstants::ItemHeight)
        throw std::runtime_error("Invalid sprite height");
    for(const auto &line : *sprite) {
        if(line.size() > InventoryConstants::ItemWidth)
            throw std::runtime_error("Invalid sprite length");
    }
    x = x_;
    y = y_;

    Display display;
    display.DrawSprite(*sprite, x, y + 1);
    display.DrawText(pitem->get_name(), x, y);
    display.DrawText(pitem->get_description(), x, y + InventoryConstants::ItemHeight + 3, InventoryConstants::ItemHintLength);
    display.DrawText("Amount: " + std::to_string(pitem->get_amount()), x, y + InventoryConstants::ItemHeight + 1);

}

ItemDrawer::~ItemDrawer() {
    Display display;
    ColorManager manager;
    std::vector<std::vector<unsigned>> EmptyWindow(InventoryConstants::ItemBoxHeight, std::vector<unsigned> (InventoryConstants::ItemBoxWidth, ' ' | manager.CreateColorPair(-1, -1)));
    display.DrawSprite(EmptyWindow, x, y);
}

void ItemDrawer::Select(bool state) {
    Display display;
    ColorManager manager;
    std::vector<std::vector<unsigned>> underline(1,
                                                 std::vector<unsigned> (InventoryConstants::ItemWidth, A_BLINK | '=' | manager.CreateColorPair(ColorManager::getColor(255, 255, 0), -1)));
    std::vector<std::vector<unsigned>> empty(1,
                                             std::vector<unsigned> (InventoryConstants::ItemWidth, ' ' | manager.CreateColorPair(-1, -1)));
    if(state) {
        display.DrawSprite(underline, x, y + InventoryConstants::ItemHeight + 2);
    }
    else {
        display.DrawSprite(empty, x, y + InventoryConstants::ItemHeight + 2);
    }
}

