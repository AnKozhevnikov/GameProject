#pragma once

#include <string>
#include <vector>
#include <functional>
#include "Message.h"

class EventListener;

class BindedData {
public:
    std::function<Message()> func;
    void *funcPtr;
    EventListener* eventListener;
    std::vector<size_t> hashes;
    std::string label;

    BindedData() = default;

    template<class C>
    BindedData(std::function<Message()> f, void* newFuncPtr, C *x, std::vector<size_t> newHashes, std::string newLabel) : func(f), funcPtr(newFuncPtr), eventListener(x), hashes(newHashes), label(newLabel) {}

    bool operator==(const BindedData &other) const {
        return funcPtr == other.funcPtr && eventListener == other.eventListener && hashes == other.hashes;
    }

    bool operator<(const BindedData &other) const {
        if (funcPtr != other.funcPtr) {
            return funcPtr < other.funcPtr;
        }
        if (eventListener != other.eventListener) {
            return eventListener < other.eventListener;
        }
        return hashes < other.hashes;
    }

    template<class C, typename Callable, typename... Args>
    static BindedData wrap(C *listener, Callable func, std::string label, Args &&... args) {
        std::vector<size_t> hashes;
        ([&]
        {
            hashes.push_back(std::hash<typename std::decay<Args>::type>{}(args));
        } (), ...);
        std::function<Message()> wrapped = std::bind(func, listener, args...);
        return BindedData(wrapped, reinterpret_cast<void*>(func), listener, hashes, label);
    }
};