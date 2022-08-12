#pragma once

#include <vector>
#include <array>
#include <iostream>

using namespace std;

// singal information for inputs and outputs of logical components
class signal {
    public:
        bool value; // on / off
        float voltage; // voltage the point of usage
        // string outputSource;

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

// perform AND boolean operation
class AndGate: public LogicGate {
    public:
        AndGate(): LogicGate() {}
        signal output() override;
};

// perform NOT boolean operation
class NotGate: public LogicGate {
    public:
        NotGate(): LogicGate() {inputCount = 1;}
        signal output() override;
};

// perform NAND boolean operation
class NandGate: public LogicGate {
    public:
        NandGate(): LogicGate() {inputCount = 2;}
        signal output() override;
};

// perform OR boolean operation
class OrGate: public LogicGate {
    public:
        OrGate(): LogicGate() {inputCount = 2;}
        signal output() override;
};

// perform NOR boolean operation
class NorGate: public LogicGate {
    public:
        NorGate(): LogicGate() {inputCount = 2;}
        signal output() override;
};

// perform XOR boolean operation
class XorGate: public LogicGate {
    public:
        XorGate(): LogicGate() {inputCount = 2;}
        signal output() override;
};
