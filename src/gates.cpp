#include <vector>
#include <iostream>

#include "gates.hpp"

using namespace std;



Signal::Signal() {
    value = 0;
    voltage = 0;
}
Signal::Signal(bool value, float voltage) {
    this->value = value;
    this->voltage = voltage;
}
Signal Signal::operator+(Signal &&rvalue) {
    return Signal(
        this->value || rvalue.value,
        (this->voltage+rvalue.voltage)/2
    );
}


// ComponentBase member functions
ComponentBase::ComponentBase(string name) { this->name = name; };
void ComponentBase::input(ComponentBase *component) {
    throw runtime_error("not intended for use");
    if (component->name == "") {} // removes compiler warning
};
Signal ComponentBase::output() { throw runtime_error("not intended for use"); };

// Input class member functions
Input::Input(string name, bool sourceValue) : ComponentBase(name) {
    _output = Signal(sourceValue, 5);
}
Signal Input::output() { return _output; }

// Component class member functions
COMPONENT_TEMPLATE
void Component<inputCount>::input(ComponentBase *source) {
    bool passed = false;
    for(size_t i = 0; i < inputCount; i++) {
        if(inputs[i] == nullptr) {
            inputs[i] = source;
            passed = true;
            break;
        }
    }
    if (!passed) {
        throw runtime_error("no open inputs in component");
    }
};

COMPONENT_TEMPLATE
Signal Component<inputCount>::output() {
    Signal tmp;
    for(size_t i = 0; i < inputCount; i++) {
        tmp = tmp + inputs[i]->output();
    }
    return tmp;
}


// This is for linking purposes only
template<> Signal Component<1>::output() {
    Signal _output;
    for(auto item: inputs) {
        _output = _output + item->output();
    }
    return _output;
}
// This is for linking purposes only
template<> Signal Component<2>::output() {
    Signal _output;
    for(auto item: inputs) {
        _output = _output + item->output();
    }
    return _output;
}

// if inputs[0] AND inputs[1] are 1 return 1
Signal AndGate::output() {
    if (inputs[0]->output().value && inputs[1]->output().value) {
        return Signal(true, 0);
    }else {
        return Signal(false, 0);
    }
}

// return the opposite of the input
Signal NotGate::output() {
    return Signal(!inputs[0]->output().value, 0);
}

// if inputs[0] AND inputs[1] are 1 return 0 otherwise 1
Signal NandGate::output() {
    if (inputs[0]->output().value && inputs[1]->output().value) {
        return Signal(false, 0);
    }else {
        return Signal(true, 0);
    }
}

// if inputs[0] OR inputs[1] 1 otherwise 0
Signal OrGate::output() {
    if (inputs[0]->output().value || inputs[1]->output().value) {
        return Signal(true, 0);
    }else {
        return Signal(false, 0);
    }
}

// if neither inputs[0] nor inputs[1] 1 otherwise 0
Signal NorGate::output() {
    if (inputs[0]->output().value || inputs[1]->output().value) {
        return Signal(false, 0);
    }else {
        return Signal(true, 0);
    }
}

// if and only if inputs[0] OR inputs[1]
Signal XorGate::output() {
    if ((inputs[0]->output().value || inputs[1]->output().value) && !(inputs[0]->output().value && inputs[1]->output().value)) {
        return Signal(true, 0);
    }else {
        return Signal(false, 0);
    }
}