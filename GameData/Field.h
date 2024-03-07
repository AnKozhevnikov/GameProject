#pragma once

#include "Cell.h"

#include <vector>

class Field {
public:
    Field();
    Field(int current_depth);
    Field(const Field &other);
    Field& operator=(const Field &field);

    void update(const Field &delta);

    std::pair<int, int> get_current() const;
    std::shared_ptr<std::pair<int, int>> get_current_ptr() const;
    void set_current(std::pair<int, int> new_current);

    int get_depth() const;
    std::shared_ptr<int> get_depth_ptr() const;
    void set_depth(int new_depth);

    std::vector<std::vector<Cell>> get_cells() const;
    std::shared_ptr<std::vector<std::vector<Cell>>> get_cells_ptr() const;
    void set_cells(const std::vector<std::vector<Cell>> &new_cells);
private:
    std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> generate(int depth);

    std::shared_ptr<std::vector<std::vector<Cell>>> cells;
    std::shared_ptr<std::pair<int, int>> current;
    std::shared_ptr<int> depth;
};