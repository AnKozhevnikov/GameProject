#pragma once

#include "Cell.h"

class Field {
public:
    Field(int current_depth = 1);
    Field& operator=(const Field &field);

    int get_depth() const;
private:
    Cell& generate(int depth);
    Cell &root;
    Cell &current;
    int depth;
};