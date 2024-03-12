#include "Field.h"

#include <memory>
#include <vector>
#include <string>

Field::Field() {
    depth=nullptr;
    current=nullptr;
    cells=nullptr;
}

Field::Field(int current_depth) {
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
        dimensions = std::make_shared<std::pair<int, int>>(*delta.dimensions);
    }

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
    //TODO: implement
    std::vector<std::vector<Cell>> v(50, std::vector<Cell>(50, Cell()));
    v[25][25]=Cell(NewEventListenerInfo(), "room");
    v[25][23]=Cell(NewEventListenerInfo(), "corridor");
    v[25][22]=Cell(NewEventListenerInfo(), "corridor");
    v[25][21]=Cell(NewEventListenerInfo(), "corridor");
    v[25][19]=Cell(NewEventListenerInfo(), "room");
    v[27][19]=Cell(NewEventListenerInfo(), "corridor");
    v[28][19]=Cell(NewEventListenerInfo(), "corridor");
    v[29][19]=Cell(NewEventListenerInfo(), "corridor");
    v[31][19]=Cell(NewEventListenerInfo(), "room");
    v[31][21]=Cell(NewEventListenerInfo(), "corridor");
    v[31][22]=Cell(NewEventListenerInfo(), "corridor");
    v[31][23]=Cell(NewEventListenerInfo(), "corridor");
    v[31][25]=Cell(NewEventListenerInfo(), "room");
    v[29][25]=Cell(NewEventListenerInfo(), "corridor");
    v[28][25]=Cell(NewEventListenerInfo(), "corridor");
    v[27][25]=Cell(NewEventListenerInfo(), "corridor");

    for (int i=24; i<=26; ++i) {
        for (int j=24; j<=26; ++j) {
            if (i!=25 || j!=25) v[i][j]=Cell(NewEventListenerInfo(), "roomborder");
        }
    }
    for (int i=24; i<=26; ++i) {
        for (int j=18; j<=20; ++j) {
            if (i!=25 || j!=19) v[i][j]=Cell(NewEventListenerInfo(), "roomborder");
        }
    }
    for (int i=30; i<=32; ++i) {
        for (int j=18; j<=20; ++j) {
            if (i!=31 || j!=19) v[i][j]=Cell(NewEventListenerInfo(), "roomborder");
        }
    }
    for (int i=30; i<=32; ++i) {
        for (int j=24; j<=26; ++j) {
            if (i!=31 || j!=25) v[i][j]=Cell(NewEventListenerInfo(), "roomborder");
        }
    }

    return std::make_pair(v, std::make_pair(25, 25)); //placeholder
}