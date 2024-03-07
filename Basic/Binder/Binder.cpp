#include "Binder.h"
#include <stdexcept>

std::function<Message()> Binder::getFunc(char c) {
    if (binded.find(c) != binded.end()) {
        return binded[c].func;
    }
    return std::bind(&Binder::empty, this);
}

void Binder::bind(int c, BindedData wrapped) {
    if (binded.find(c) != binded.end()) {
        throw std::invalid_argument("Key already binded");
    }
    //Do something with label
    binded[c] = wrapped;
}

void Binder::bind_no_charachter(BindedData wrapped) {
    noCharachter.insert(wrapped);
}

void Binder::unbind(int c) {
    //Do something with label
    binded.erase(c);
}

const std::set<BindedData>& Binder::getNoCharachter() const {
    return noCharachter;
}

void Binder::stop(BindedData wrapped) {
    std::set<char> toErase;
    for (auto it = binded.begin(); it != binded.end(); it++) {
        if (it->second == wrapped) {
            //Do something with label
            toErase.insert(it->first);
        }
    }
    for (auto it = toErase.begin(); it != toErase.end(); it++) {
        binded.erase(*it);
    }

    std::set<BindedData> toEraseNoCharachter;
    for (auto it = noCharachter.begin(); it != noCharachter.end(); it++) {
        if (*it == wrapped) {
            toEraseNoCharachter.insert(*it);
        }
    }
    for (auto it = toEraseNoCharachter.begin(); it != toEraseNoCharachter.end(); it++) {
        noCharachter.erase(*it);
    }
}