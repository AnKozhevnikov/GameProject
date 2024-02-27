#include "Binder.h"

const std::function<Message()> Binder::getFunc(char c) {
    //TODO: implement
    const std::function<Message()> ret = std::bind(&Binder::empty, this);
    return ret;
}