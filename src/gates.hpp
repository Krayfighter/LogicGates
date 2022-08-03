#pragma once

#include <vector>
#include <iostream>

using namespace std;

// singal information for inputs and outputs of logical components
class signal {
    public:
        bool value; // on / off
        float voltage; // voltage the point of usage

        signal();
        signal(bool value, float voltage);
        bool operator==(const signal *operand);
        bool operator!=(const signal *operand);
};

// base class for all basic logic components
class LogicGate {
    public:
        vector<signal> inputs; // vector of inputs to the components
        unsigned int inputCount = 2; // number of inputs for to take
        // signal _output; // output variabe

        LogicGate() {};
        virtual signal output() {return signal();}; // virtual output function for all subclasses to implement
        void input(LogicGate *source);
};

// class for inputs connections to the diagram (takes no inputs)
class LogicSource: public LogicGate {
    public:
        signal _output;
        LogicSource(bool sourceValue);
        signal output() override;
};

class AndGate: public LogicGate {
    public:
        AndGate(): LogicGate() {}
        signal output() override;
};

class NotGate: public LogicGate {
    public:
        NotGate(): LogicGate() {inputCount = 1;}
        signal output() override;
};