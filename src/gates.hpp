#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <memory>

using namespace std;

// singal information for inputs and outputs of logical components
class wire {
    public:
        bool value; // on / off
        float voltage; // voltage the point of usage
        // string outputSource;

        wire();
        wire(bool value, float voltage);
        void setValue(bool value, float voltage);
        shared_ptr<wire> getValue();
        // bool operator==(const wire *operand);
        // bool operator!=(const wire *operand);
};

// class for inputs connections to the diagram (takes no inputs)
class LogicSource: public wire {
    public:
        LogicSource(bool sourceValue): wire(sourceValue, 5) {}
};

// base class for all basic logic components
class LogicGate {
    public:
        vector<shared_ptr<wire>> inputs; // vector of inputs to the components
        unsigned int inputCount = 2; // number of inputs for to take
        // wire _output; // output variabe

        LogicGate() {};
        virtual unique_ptr<wire> output() {return unique_ptr<wire> (new wire(0, -1));}; // virtual output function for all subclasses to implement
        void input(shared_ptr<wire> source);
};

// perform AND boolean operation
class AndGate: public LogicGate {
    public:
        AndGate(): LogicGate() {}
        unique_ptr<wire> output() override;
};

// perform NOT boolean operation
class NotGate: public LogicGate {
    public:
        NotGate(): LogicGate() {inputCount = 1;}
        unique_ptr<wire> output() override;
};

// perform NAND boolean operation
class NandGate: public LogicGate {
    public:
        NandGate(): LogicGate() {inputCount = 2;}
        unique_ptr<wire> output() override;
};

// perform OR boolean operation
class OrGate: public LogicGate {
    public:
        OrGate(): LogicGate() {inputCount = 2;}
        unique_ptr<wire> output() override;
};

// perform NOR boolean operation
class NorGate: public LogicGate {
    public:
        NorGate(): LogicGate() {inputCount = 2;}
        unique_ptr<wire> output() override;
};

// perform XOR boolean operation
class XorGate: public LogicGate {
    public:
        XorGate(): LogicGate() {inputCount = 2;}
        unique_ptr<wire> output() override;
};
