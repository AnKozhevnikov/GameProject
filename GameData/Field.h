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
    const std::unique_ptr<std::pair<int, int>> &get_current_ptr() const;
    void set_current(std::pair<int, int> new_current);

    int get_depth() const;
    const std::unique_ptr<int> &get_depth_ptr() const;
    void set_depth(int new_depth);

    std::vector<std::vector<Cell>> get_cells() const;
    const std::unique_ptr<std::vector<std::vector<Cell>>> &get_cells_ptr() const;
    void set_cells(const std::vector<std::vector<Cell>> &new_cells);
private:
    std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> generate(int depth);

    std::unique_ptr<std::vector<std::vector<Cell>>> cells;
    std::unique_ptr<std::pair<int, int>> current;
    std::unique_ptr<int> depth;
};