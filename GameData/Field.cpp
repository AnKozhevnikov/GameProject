#include "Field.h"

#include <memory>

std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> Field::generate(int depth) {
    //TODO: implement
    Cell root;
    std::vector<std::vector<Cell>> v(1, std::vector<Cell>(1, root));
    return std::make_pair(v, std::make_pair(0, 0)); //placeholder
}

Field::Field(int current_depth) {
    depth = current_depth;
    std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> new_field = generate(current_depth);
    cells = new_field.first;
    current = new_field.second;
}

Field& Field::operator=(const Field &field) {
    cells = field.cells;
    current = field.current;
    depth = field.depth;
    return *this;
}

const int& Field::get_depth() const {
    return depth;
}

const std::pair<int, int>& Field::get_current() const {
    return current;
}

const std::vector<std::vector<Cell>>& Field::get_cells() const {
    return cells;
}

void Field::set_current(const std::pair<int, int>& new_current) {
    current = new_current;
}