#pragma once

#include <vector>
#include <array>
#include <type_traits>

#include "gates.hpp"


// // Conbination of Logical Operations that can produce a specified number of output values
// template <class inner, int outputCount>
// class LogicUnit {
//     public:
//         LogicUnit() {
//             static_assert(is_base_of<LogicGate, inner>::value, "provided class in not subclass on LogicGate");
//         }
//         array<signal, outputCount> outputs;
// };

struct NamedLogicGate {
    string name;
    LogicGate *gate;
};

class Circuit {
    // private:
    public:
        unsigned int inputCount;
        vector<wire> inputs;
        vector<shared_ptr<wire>> outputs;
        vector<wire> wires;
        vector<NamedLogicGate> components;
        Circuit() {};
        LogicGate *searchGate(string name);
        wire *newWire();
};