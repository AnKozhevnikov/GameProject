#pragma once

#include <string>
#include <vector>
#include <memory>

class Item {
public:
    Item() = default;
    Item(std::string name, int amount, std::vector<std::vector<unsigned>> sprite);
    Item(const Item &other);
    Item& operator=(const Item &other);

    std::string get_name() const;
    std::shared_ptr<std::string> get_name_ptr() const;
    void set_name(std::string newName);

    int get_amount() const;
    std::shared_ptr<int> get_amount_ptr() const;
    void set_amount(int newAmount);

    std::vector<std::vector<unsigned>> get_sprite() const;
    std::shared_ptr<std::vector<std::vector<unsigned>>> get_sprite_ptr() const;
    void set_sprite(const std::vector<std::vector<unsigned>> &newSprite);

    std::string get_description() const;
    std::shared_ptr<std::string> get_description_ptr() const;
    void set_description(std::string newDescription);

    void update(const Item &delta);

private:
    std::shared_ptr<std::string> name;
    std::shared_ptr<int> amount;
    std::shared_ptr<std::vector<std::vector<unsigned>>> sprite;
    std::shared_ptr<std::string> description;
};