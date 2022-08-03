#include <vector>
#include <iostream>

#include "gates.hpp"

using namespace std;


signal::signal() {
    value = false;
    voltage = 0;
}
signal::signal(bool value, float voltage) {
    this->value = value;
    this->voltage = voltage;
}
bool signal::operator==(const signal *operand) {
    if (this->value == operand->value && this->voltage == operand->voltage) {
        return true;
    }else {
        return false;
    }
}
bool signal::operator!=(const signal *operand) {
    if (this==operand) {
        return false;
    }else {
        return true;
    }
}


void LogicGate::input(LogicGate *source) {
    if (inputs.size() >= inputCount) {
        throw std::runtime_error("too many logic gate inputs");
    }else{
        inputs.push_back(source->output());
    }
}


LogicSource::LogicSource(bool sourceValue) {
    inputCount = 0;
    _output = signal(sourceValue, 5);
}
signal LogicSource::output() {
    return _output;
}


signal AndGate::output() {
    if (inputs[0].value && inputs[1].value) {
        return signal(true, 0);
    }else {
        return signal(false, 0);
    }
}


signal NotGate::output() {
    return signal(!inputs[0].value, 0);
}