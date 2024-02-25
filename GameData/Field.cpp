#include "Field.h"
#include "EventGetter.h"

#include <memory>

Cell& Field::generate(int depth) {
    std::shared_ptr<Cell> a = std::make_shared<Cell>();
    return *a; //placeholder
    //TODO: implement
}

Field::Field(int current_depth) : depth(current_depth), root(generate(depth)), current(root) {}

Field& Field::operator=(const Field &field) {
    root = field.root;
    current = field.current;
    depth = field.depth;
    return *this;
}

int Field::get_depth() const {
    return depth;
}