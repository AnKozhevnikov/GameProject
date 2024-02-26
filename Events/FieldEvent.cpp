#include "FieldEvent.h"

std::shared_ptr<void> FieldEvent::run_event() {
    //TODO: implement
    std::shared_ptr<std::pair<int, int>> p = std::make_shared<std::pair<int, int>>();
    return std::static_pointer_cast<void>(p);
}