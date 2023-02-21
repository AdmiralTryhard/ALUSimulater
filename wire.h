#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>


class WireObject;
using Wire = std::shared_ptr<WireObject>;
using Wires = std::vector<Wire>;

using Action = std::function<void()>;
using Actions = std::vector<Action>;

class WireObject {
public:
    WireObject(std::string label);
    std::string get_label() const;
    void set(bool value);
    bool get() const;
    void on_change(Action action);

private:
    std::string label;
    bool value;
    Actions actions;
};

Wire make_wire(std::string label);

void probe(Wire wire);
