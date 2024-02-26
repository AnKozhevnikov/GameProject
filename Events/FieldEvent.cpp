#include "FieldEvent.h"

std::shared_ptr<void> FieldEvent::run_event() {
    //TODO: implement
    std::shared_ptr<Field> field = std::make_shared<Field>();
    return std::static_pointer_cast<void>(field);
}