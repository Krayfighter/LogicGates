#include <iostream>
#include <vector>

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
// LogicGate::LogicGate(bool sourceValue) {
//     inputCount = 1;
//     inputs.push_back(signal(sourceValue, 5));
// }
void LogicGate::input(LogicGate *source) {
    if (inputs.size() >= inputCount) {
        throw std::runtime_error("too many logic gate inputs");
    }else{
        inputs.push_back(source->output());
    }
}

class LogicSource: public LogicGate {
    public:
        LogicSource(bool sourceValue);
        signal output() override;
};
LogicSource::LogicSource(bool sourceValue) {
    inputCount = 0;
    _output = signal(sourceValue, 5);
}
signal LogicSource::output() {
    return _output;
}

class AndGate: public LogicGate {
    public:
        AndGate(): LogicGate() {}
        signal output() override;
};
signal AndGate::output() {
    if (inputs[0].value && inputs[1].value) {
        return signal(true, 0);
    }else {
        return signal(false, 0);
    }
}

class NotGate: public LogicGate {
    public:
        NotGate(): LogicGate() {inputCount = 1;}
        signal output() override;
};
signal NotGate::output() {
    return signal(!inputs[0].value, 0);
}


int main(int argc, char **argv) {
    LogicSource in1(1);
    LogicSource in2(0);
    NotGate reverse;
    AndGate combine;

    combine.input(&in1);
    reverse.input(&in2);
    combine.input(&reverse);


    cout << in1.output().value << " " << in2.output().value << endl;
    cout << "| " << reverse.output().value  << endl;
    cout << "\\ /" << endl;
    cout << " " << combine.output().value << endl;

    // cout << combine.output().value << endl;
}