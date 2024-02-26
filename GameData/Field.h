#pragma once

#include "Cell.h"
#include "Drawer.h"

#include <vector>

class Field {
public:
    Field(int current_depth = 1);
    Field& operator=(const Field &field);

    const int& get_depth() const;
    const std::pair<int, int>& get_current() const;
    const std::vector<std::vector<Cell>>& get_cells() const;

    void set_current(const std::pair<int, int>& new_current);
private:
    std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> generate(int depth);
    std::vector<std::vector<Cell>> cells;
    std::pair<int, int> current;
    int depth;
};