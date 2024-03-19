#include "Item.h"

Item::Item(std::string name, int amount, std::vector<std::vector<unsigned>> sprite, std::string description, Ability ability) {
    this->name = std::make_shared<std::string>(name);
    this->amount = std::make_shared<int>(amount);
    this->sprite = std::make_shared<std::vector<std::vector<unsigned>>>(sprite);
    this->description = std::make_shared<std::string>(description);
    this->ability = std::make_shared<Ability>(ability);
}

Item::Item(const Item &other) {
    name = std::make_shared<std::string>(*other.name);
    amount = std::make_shared<int>(*other.amount);
    sprite = std::make_shared<std::vector<std::vector<unsigned>>>(*other.sprite);
    description = std::make_shared<std::string>(*other.description);
    ability = std::make_shared<Ability>(*other.ability);
}

Item& Item::operator=(const Item &other) {
    name = std::make_shared<std::string>(*other.name);
    amount = std::make_shared<int>(*other.amount);
    sprite = std::make_shared<std::vector<std::vector<unsigned>>>(*other.sprite);
    description = std::make_shared<std::string>(*other.description);
    ability = std::make_shared<Ability>(*other.ability);
    
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

std::string Item::get_description() const {
    return *description;
}

std::shared_ptr<std::string> Item::get_description_ptr() const {
    return description;
}

void Item::set_description(std::string newDescription) {
    description = std::make_shared<std::string>(newDescription);
}

Ability Item::get_ability() const {
    return *ability;
}

std::shared_ptr<Ability> Item::get_ability_ptr() const {
    return ability;
}

void Item::set_ability(Ability newAbility) {
    ability = std::make_shared<Ability>(newAbility);
}

void Item::update(const Item &delta) {
    if (delta.name != nullptr) {
        if (name == nullptr) name = std::make_shared<std::string>();
        name = delta.name;
    }
    if (delta.amount != nullptr) {
        if (amount == nullptr) amount = std::make_shared<int>();
        amount = delta.amount;
    }
    if (delta.sprite != nullptr) {
        if (sprite == nullptr) sprite = std::make_shared<std::vector<std::vector<unsigned>>>();
        sprite = delta.sprite;
    }
    if (delta.description != nullptr) {
        if (description == nullptr) description = std::make_shared<std::string>();
        description = delta.description;
    }
}

