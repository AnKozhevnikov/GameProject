#include "Binder.h"
#include "Display.h"
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
    Display display;
    display.SendBind(Bind(c, true, wrapped.label));
    binded[c] = wrapped;
}

void Binder::bind_no_charachter(BindedData wrapped) {
    noCharachter.insert(wrapped);
}

void Binder::unbind(int c) {
    Display display;
    if (binded.find(c)!=binded.end()) {
        display.SendBind(Bind(c, false, binded[c].label));
    }
    binded.erase(c);
}

const std::set<BindedData>& Binder::getNoCharachter() const {
    return noCharachter;
}

bool Binder::exists(BindedData d) {
    return noCharachter.find(d) != noCharachter.end();
}

void Binder::stop(BindedData wrapped) {
    std::set<char> toErase;
    for (auto it = binded.begin(); it != binded.end(); it++) {
        if (it->second == wrapped) {
            Display display;
            display.SendBind(Bind(it->first, false, it->second.label));
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