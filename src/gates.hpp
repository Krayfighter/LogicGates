#pragma once

#include <vector>
#include <iostream>

using namespace std;

class signal {
    public:
        bool value;
        float voltage;

        signal();
        signal(bool value, float voltage);
        bool operator==(const signal *operand);
        bool operator!=(const signal *operand);
};

// template<function output>
class LogicGate {
    public:
        vector<signal> inputs;
        unsigned int inputCount = 2;
        signal _output;

        LogicGate() {};
        // LogicGate(bool sourceValue);
        virtual signal output() {return signal();};
        void input(LogicGate *source);
        // void setinputCount(int length) {inputCount = length;}
};

class LogicSource: public LogicGate {
    public:
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