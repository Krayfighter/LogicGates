#include <vector>
#include <iostream>

#include "gates.hpp"

using namespace std;

// *** singal implementations
wire::wire() {
    value = false;
    voltage = 0;
}
wire::wire(bool value, float voltage) {
    this->value = value;
    this->voltage = voltage;
}
void wire::setValue(bool value, float voltage) {
    this->value = value, this->voltage = voltage;
}
shared_ptr<wire> wire::getValue() {return (shared_ptr<wire>) this;}
//  // if both wires share the same value and voltage returns true
// bool wire::operator==(const wire *operand) {
//     if (this->value == operand->value && this->voltage == operand->voltage) {
//         return true;
//     }else {
//         return false;
//     }
// }
//  // the inverse of wire::operator==();
// bool wire::operator!=(const wire *operand) {
//     if (this==operand) {
//         return false;
//     }else {
//         return true;
//     }
// }

// adds another LogicGate's output to the `inputs` vector
void LogicGate::input(shared_ptr<wire> source) {
    if (inputs.size() >= inputCount) {
        throw std::runtime_error("too many logic gate inputs");
    }else{
        inputs.push_back(source);
    }
}

// // init logic source with a value (1, 0), (true, false)
// LogicSource::LogicSource(bool sourceValue) {
//     inputCount = 0;
//     _output = wire(sourceValue, 5);
// }
// unique_ptr<wire> LogicSource::output() {
//     return (unique_ptr<wire>) &_output;
// }

// if inputs[0] AND inputs[1] are 1 return 1
unique_ptr<wire> AndGate::output() {
    if (inputs[0]->value && inputs[1]->value) {
        return (unique_ptr<wire>) new wire(true, 0);
    }else {
        return (unique_ptr<wire>) new wire(false, 0);
    }
}

// return the opposite of the input
unique_ptr<wire> NotGate::output() {
    return (unique_ptr<wire>) new wire(!inputs[0]->value, 0);
}

// if inputs[0] AND inputs[1] are 1 return 0 otherwise 1
unique_ptr<wire> NandGate::output() {
    if (inputs[0]->value && inputs[1]->value) {
        return (unique_ptr<wire>) new wire(false, 0);
    }else {
        return (unique_ptr<wire>) new wire(true, 0);
    }
}

// if inputs[0] OR inputs[1] 1 otherwise 0
unique_ptr<wire> OrGate::output() {
    if (inputs[0]->value || inputs[1]->value) {
        return (unique_ptr<wire>) new wire(true, 0);
    }else {
        return (unique_ptr<wire>) new wire(false, 0);
    }
}

// if neither inputs[0] nor inputs[1] 1 otherwise 0
unique_ptr<wire> NorGate::output() {
    if (inputs[0]->value || inputs[1]->value) {
        return (unique_ptr<wire>) new wire(false, 0);
    }else {
        return (unique_ptr<wire>) new wire(true, 0);
    }
}

// if and only if inputs[0] OR inputs[1]
unique_ptr<wire> XorGate::output() {
    if ((inputs[0]->value || inputs[1]->value) && !(inputs[0]->value && inputs[1]->value)) {
        return (unique_ptr<wire>) new wire(true, 0);
    }else {
        return (unique_ptr<wire>) new wire(false, 0);
    }
}