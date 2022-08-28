#include <string>

#include "gates.hpp"
#include "diagram.hpp"
#include "parser.hpp"



Circuit::Circuit(string fileSource, bool recreate): ComponentBase(fileSource) {
    if (recreate) {
        *this = parseFile(fileSource);
    }
}
void Circuit::input(ComponentBase *component) {
    outputs.push_back(component);
}
void Circuit::logCircuitOutput() {
    Signal tmp;
    for(size_t i = 0; i < outputs.size(); i++) {
        tmp = outputs[i]->output();
        cout << "name: " << outputs[i]->name << endl;
        cout << "value: " << tmp.value << ", voltage: " << tmp.voltage << endl;
    }
}

// search for a LogicGate in `circuit.components` by name
// LogicGate *Circuit::searchGate(string name) {
//     bool namefound = false;
//     for (auto component: components) {
//         if (component.name == name) {
//             return component.gate;
//         }else continue;
//     }
//     if (!namefound) {
//         throw runtime_error("component name not found in components during parse");
//     }
//     return new LogicGate(); // redundant | here to stop compiler warning
//     // warning: control reaches end of non-void function [-Wreturn-type]
// }
// wire *Circuit::newWire() {
//     wires.push_back(wire());
//     return &wires[
//         wires.size()-1
//     ];
// }