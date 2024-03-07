#include "Field.h"

#include <memory>
#include <vector>

Field::Field() {
    depth=nullptr;
    current=nullptr;
    cells=nullptr;
}

Field::Field(int current_depth) {
    depth = std::make_shared<int>(current_depth);
    std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> new_field = generate(current_depth);
    cells = std::make_shared<std::vector<std::vector<Cell>>>(new_field.first);
    current = std::make_shared<std::pair<int, int>>(new_field.second);
}

Field::Field(const Field &other) {
    cells = std::make_shared<std::vector<std::vector<Cell>>>(*other.cells);
    current = std::make_shared<std::pair<int, int>>(*other.current);
    depth = std::make_shared<int>(*other.depth);
}

Field& Field::operator=(const Field &field) {
    if (field.cells != nullptr) cells = std::make_shared<std::vector<std::vector<Cell>>>(*field.cells);
    else cells = nullptr;

    if (field.current != nullptr) current = std::make_shared<std::pair<int, int>>(*field.current);
    else current = nullptr;

    if (field.depth != nullptr) depth = std::make_shared<int>(*field.depth);
    else depth = nullptr;
    
    return *this;
}

void Field::update(const Field &delta) {
    if (delta.cells != nullptr) {
        for (int i=0; i<(*delta.cells).size(); i++) {
            for (int j=0; j<(*delta.cells)[i].size(); j++) {
                (*cells)[i][j].update((*delta.cells)[i][j]);
            }
        }
    }
    if (delta.current != nullptr) {
        current = std::make_shared<std::pair<int, int>>(*delta.current);
    }
    if (delta.depth != nullptr) {
        depth = std::make_shared<int>(*delta.depth);
    }
}

int Field::get_depth() const {
    return *depth;
}

std::shared_ptr<int> Field::get_depth_ptr() const {
    return depth;
}

void Field::set_depth(int new_depth) {
    depth = std::make_shared<int>(new_depth);
}

std::pair<int, int> Field::get_current() const {
    return *current;
}

std::shared_ptr<std::pair<int, int>> Field::get_current_ptr() const {
    return current;
}

void Field::set_current(std::pair<int, int> new_current) {
    current = std::make_shared<std::pair<int, int>>(new_current);
}

std::vector<std::vector<Cell>> Field::get_cells() const {
    return *cells;
}

std::shared_ptr<std::vector<std::vector<Cell>>> Field::get_cells_ptr() const {
    return cells;
}

void Field::set_cells(const std::vector<std::vector<Cell>> &new_cells) {
    cells = std::make_shared<std::vector<std::vector<Cell>>>(new_cells);
}

std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> Field::generate(int depth) {
    //TODO: implement
    Cell root("","");
    std::vector<std::vector<Cell>> v(1, std::vector<Cell>(1, root));
    return std::make_pair(v, std::make_pair(0, 0)); //placeholder
}