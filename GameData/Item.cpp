#include "Item.h"

Item::Item(std::string name, int amount, std::vector<std::vector<unsigned>> sprite) {
    this->name = std::make_shared<std::string>(name);
    this->amount = std::make_shared<int>(amount);
    this->sprite = std::make_shared<std::vector<std::vector<unsigned>>>(sprite);
}

Item::Item(const Item &other) {
    name = std::make_shared<std::string>(*other.name);
    amount = std::make_shared<int>(*other.amount);
    sprite = std::make_shared<std::vector<std::vector<unsigned>>>(*other.sprite);
}

Item& Item::operator=(const Item &other) {
    name = std::make_shared<std::string>(*other.name);
    amount = std::make_shared<int>(*other.amount);
    sprite = std::make_shared<std::vector<std::vector<unsigned>>>(*other.sprite);
    
    return *this;
}

std::string Item::get_name() const {
    return *name;
}

std::shared_ptr<std::string> Item::get_name_ptr() const {
    return name;
}

void Item::set_name(std::string newName) {
    name = std::make_shared<std::string>(newName);
}

int Item::get_amount() const {
    return *amount;
}

std::shared_ptr<int> Item::get_amount_ptr() const {
    return amount;
}

void Item::set_amount(int newAmount) {
    amount = std::make_shared<int>(newAmount);
}

std::vector<std::vector<unsigned>> Item::get_sprite() const {
    return *sprite;
}

std::shared_ptr<std::vector<std::vector<unsigned>>> Item::get_sprite_ptr() const {
    return sprite;
}

void Item::set_sprite(const std::vector<std::vector<unsigned>> &newSprite) {
    sprite = std::make_shared<std::vector<std::vector<unsigned>>>(newSprite);
}

void Item::update(const Item &delta) {
    if (delta.name != nullptr) {
        name = delta.name;
    }
    if (delta.amount != nullptr) {
        amount = delta.amount;
    }
    if (delta.sprite != nullptr) {
        sprite = delta.sprite;
    }
}

