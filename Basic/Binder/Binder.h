#pragma once

#include "BindedData.h"
#include <functional>
#include <map>
#include <set>

class Binder {
public:
    Binder() = default;
    std::function<Message()> getFunc(char c);

    void bind(int c, BindedData wrapped);
    void bind_no_charachter(BindedData wrapped);

    void unbind(int c);
    const std::set<BindedData>& getNoCharachter() const;
    void stop(BindedData wrapped);
private:
    std::map<int, BindedData> binded;
    std::set<BindedData> noCharachter;
    Message empty() {
        return Message();
    }
};