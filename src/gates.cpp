#include <vector>
#include <iostream>

#include "gates.hpp"

using namespace std;

// *** singal implementations
signal::signal() {
    value = false;
    voltage = 0;
}
signal::signal(bool value, float voltage) {
    this->value = value;
    this->voltage = voltage;
}
 // if both signals share the same value and voltage returns true
bool signal::operator==(const signal *operand) {
    if (this->value == operand->value && this->voltage == operand->voltage) {
        return true;
    }else {
        return false;
    }
}
 // the inverse of signal::operator==();
bool signal::operator!=(const signal *operand) {
    if (this==operand) {
        return false;
    }else {
        return true;
    }
}

// adds another LogicGate's output to the `inputs` vector
void LogicGate::input(LogicGate *source) {
    if (inputs.size() >= inputCount) {
        throw std::runtime_error("too many logic gate inputs");
    }else{
        inputs.push_back(source->output());
    }
}

// init logic source with a value (1, 0), (true, false)
LogicSource::LogicSource(bool sourceValue) {
    inputCount = 0;
    _output = signal(sourceValue, 5);
}
signal LogicSource::output() {
    return _output;
}

// if inputs[0] AND inputs[1] are 1 return 1
signal AndGate::output() {
    if (inputs[0].value && inputs[1].value) {
        return signal(true, 0);
    }else {
        return signal(false, 0);
    }
}

// return the opposite of the input
signal NotGate::output() {
    return signal(!inputs[0].value, 0);
}