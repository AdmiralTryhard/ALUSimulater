#include "wire.h"
#include <iostream>

WireObject::WireObject(std::string label)
    :label{label}, value{false} {}

std::string WireObject::get_label() const {
    return label;
}

void WireObject::set(bool new_value) {
    // Implement me:
    if(new_value == value){
        return;
    }
    value = new_value;
    // 3. Run all actions

    for (Action a : actions){
        
    }
}

bool WireObject::get() const {
    return value;
}

void WireObject::on_change(Action action) {
    // Implement me:
    action();
    actions.push_back(action);
    // 1. Run the action before adding it. This makes the wire value
    //    propagate as other wires are connected to it.
    // 2. Add the action to actions
}

Wire make_wire(std::string label) {
    return std::make_shared<WireObject>(label);
}

void probe(Wire wire) {
    // A circular reference is created if the shared_ptr to the Wire is
    // stored in the lambda that is given to Wire::on_change. The
    // circular reference prevents the WireObject from being deleted
    // when it goes out of scope - leaking memory. To avoid this, only
    // store raw pointers of a WireObject inside the lambda.
    auto pwire = wire.get(); // get the raw pointer
    auto print_value = [=](){ std::cout << pwire->get_label() << " set to " << pwire->get() << '\n'; };
    wire->on_change(print_value);
}
