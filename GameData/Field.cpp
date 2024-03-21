#include "Field.h"
#include "DungeonGraph.h"

#include <memory>
#include <vector>
#include <string>

Field::Field() {
    depth=nullptr;
    current=nullptr;
    cells=nullptr;
}

Field::Field(int current_depth, std::shared_ptr<std::vector<Hero>> heroes) {
    dimensions = std::make_shared<std::pair<int, int>>(std::make_pair(50, 50));
    depth = std::make_shared<int>(current_depth);
    std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> new_field = generate(current_depth);
    cells = std::make_shared<std::vector<std::vector<Cell>>>(new_field.first);
    current = std::make_shared<std::pair<int, int>>(new_field.second);
}

Field::Field(const Field &other) {
    dimensions = std::make_shared<std::pair<int, int>>(*other.dimensions);
    cells = std::make_shared<std::vector<std::vector<Cell>>>(*other.cells);
    current = std::make_shared<std::pair<int, int>>(*other.current);
    depth = std::make_shared<int>(*other.depth);
}

Field& Field::operator=(const Field &field) {
    if (field.dimensions != nullptr) dimensions = std::make_shared<std::pair<int, int>>(*field.dimensions);
    else dimensions = nullptr;

    if (field.cells != nullptr) cells = std::make_shared<std::vector<std::vector<Cell>>>(*field.cells);
    else cells = nullptr;

    if (field.current != nullptr) current = std::make_shared<std::pair<int, int>>(*field.current);
    else current = nullptr;

    if (field.depth != nullptr) depth = std::make_shared<int>(*field.depth);
    else depth = nullptr;
    
    return *this;
}

void Field::update(const Field &delta) {
    if (delta.dimensions != nullptr) {
        if (dimensions == nullptr) dimensions = std::make_shared<std::pair<int, int>>();
        dimensions = std::make_shared<std::pair<int, int>>(*delta.dimensions);
    }

    if (delta.cells != nullptr) {
        if (cells == nullptr) cells = std::make_shared<std::vector<std::vector<Cell>>>(dimensions->first, std::vector<Cell>(dimensions->second));
        for (int i=0; i<(*delta.cells).size(); i++) {
            for (int j=0; j<(*delta.cells)[i].size(); j++) {
                (*cells)[i][j].update((*delta.cells)[i][j]);
            }
        }
    }
    if (delta.current != nullptr) {
        if (current == nullptr) current = std::make_shared<std::pair<int, int>>();
        current = std::make_shared<std::pair<int, int>>(*delta.current);
    }
    if (delta.depth != nullptr) {
        if (depth == nullptr) depth = std::make_shared<int>();
        depth = std::make_shared<int>(*delta.depth);
    }
}

std::pair<int, int> Field::get_dimensions() const {
    return *dimensions;
}

std::shared_ptr<std::pair<int, int>> Field::get_dimensions_ptr() const {
    return dimensions;
}

void Field::set_dimensions(std::pair<int, int> new_dimensions) {
    dimensions = std::make_shared<std::pair<int, int>>(new_dimensions);
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
    std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> result = DungeonGenerator::generateDungeons(depth, 50, 50, 20);
    return result;
}