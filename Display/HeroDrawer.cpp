#include "HeroDrawer.h"
#include "Display.h"
#include "BattleViewManager.h"
#include "stdexcept"
#include <vector>

HeroDrawer::HeroDrawer(PHero phero, int x_, int y_) {
    x = x_;
    y = y_;
    Display display;

    std::shared_ptr<std::vector<std::vector<unsigned int>>> sprite = phero->get_sprite_ptr();
    if(sprite->size() != BattleViewManager::HeroHeight) throw std::runtime_error("Invalid sprite height");
    for(const auto &line : *sprite) {
        if(line.size() > BattleViewManager::HeroLength)
            throw std::runtime_error("Invalid sprite length");
    }
    display.DrawSprite(*sprite, x, y);

    //TODO Apply Effects
}

void HeroDrawer::SetChoice(bool state) {
    Display display;
    if(state) {
        display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (BattleViewManager::HeroLength, ' ' | COLOR_YELLOW | A_BLINK)), x, y + BattleViewManager::HeroHeight + 1);
    }
    else{
        ColorManager manager;
        display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (BattleViewManager::HeroLength, ' ' | manager.CreateColorPair(-1, -1))), x, y + BattleViewManager::HeroHeight + 1);
    }
}

void HeroDrawer::SetHp(int cur_hp, int max_hp) {
    Display display;
    std::string hp = std::to_string(cur_hp) + "/" + std::to_string(max_hp) + " HP";
    display.DrawText(std::string(BattleViewManager::HeroLength, ' '), x, y + BattleViewManager::HeroHeight + 2); //Clear old hp
    display.DrawText(hp, x, y + BattleViewManager::HeroHeight + 2); //Draw new hp
}

void HeroDrawer::SetDmg(int value) {
    Display display;
    std::string dmg = std::to_string(value) + " DMG";
    display.DrawText(std::string(BattleViewManager::HeroLength / 2, ' '), x, y + BattleViewManager::HeroHeight + 3); //Clear old dmg
    display.DrawText(dmg, x, y + BattleViewManager::HeroHeight + 3); //Draw new dmg
}

void HeroDrawer::SetAttention(int value) {
    Display display;
    std::string attention = std::to_string(value) + " ATT";
    display.DrawText(std::string(BattleViewManager::HeroLength / 2, ' '), x + BattleViewManager::HeroLength / 2, y + BattleViewManager::HeroHeight + 3); //Clear old attention
    display.DrawText(attention, x + BattleViewManager::HeroLength / 2, y + BattleViewManager::HeroHeight + 3); //Draw new attention
}

void HeroDrawer::SetName(const std::string &name) {
    Display display;
    display.DrawText(std::string(BattleViewManager::HeroLength, ' '), x, y - 1); //Clear old name
    display.DrawText(name, x, y - 1); //Draw new name
}

void HeroDrawer::SetInitiative(int value) {
    Display display;
    std::string initiative = std::to_string(value) + " INIT";
    display.DrawText(std::string(BattleViewManager::HeroLength, ' '), x, y + BattleViewManager::HeroHeight + 4); //Clear old initiative
    display.DrawText(initiative, x, y + BattleViewManager::HeroHeight + 4); //Draw new initiative
}

HeroDrawer::~HeroDrawer() {
    Display display;
    display.DrawSprite(std::vector<std::vector<unsigned>> (BattleViewManager::HeroHeight + 5,
                std::vector<unsigned> (BattleViewManager::HeroLength, ' ')), x, y-1);
}

void HeroDrawer::ApplyEffect(VisualEffect effect, bool state) const {
    Display display;
    ColorManager manager;
    switch(effect) {
        //Placeholders for now, will change later
        case VisualEffect::BURN:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_RED, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::STUN:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_YELLOW, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::HEAL:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_GREEN, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::DEAD:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_BLACK, COLOR_RED))), x, y + BattleViewManager::HeroHeight + 5);
            break;
        case VisualEffect::SELECT:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_YELLOW, -1))), x, y + BattleViewManager::HeroHeight + 5);
            break;
    }
}