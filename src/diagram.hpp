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
        vector<LogicSource> inputs;
        vector<NamedLogicGate> components;
        vector<signal> outputs;
        Circuit() {};
        LogicGate *searchGate(string name);
};