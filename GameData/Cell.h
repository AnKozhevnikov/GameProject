#pragma once

#include <string>
#include <vector>

class Cell {
public:
    enum class direction {UP, DOWN, LEFT, RIGHT};
    Cell() = default;
private:
    int x,y;
    std::string event_type;
    std::string room_type;
    std::vector<std::pair<direction, Cell&>> neighbors;
};