#include <string>

#include "gates.hpp"
#include "diagram.hpp"

// search for a LogicGate in `circuit.components` by name
LogicGate *Circuit::searchGate(string name) {
    bool namefound = false;
    for (auto component: components) {
        if (component.name == name) {
            return component.gate;
        }else continue;
    }
    if (!namefound) {
        throw runtime_error("component name not found in components during parse");
    }
    return new LogicGate(); // redundant | here to stop compiler warning
    // warning: control reaches end of non-void function [-Wreturn-type]
}