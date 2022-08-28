#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <memory>

#define COMPONENT_TEMPLATE template <size_t inputCount>

using namespace std;

// // singal information for inputs and outputs of logical components
// class wire {
//     public:
//         bool value; // on / off
//         float voltage; // voltage the point of usage
//         // string outputSource;

//         wire();
//         wire(bool value, float voltage);
//         void setValue(bool value, float voltage);
//         shared_ptr<wire> getValue();
//         // bool operator==(const wire *operand);
//         // bool operator!=(const wire *operand);
// };

struct Signal {
    bool value;
    float voltage;
    Signal();
    Signal(bool value, float voltage);
    Signal operator+(Signal &&rvalue);
};

class ComponentBase {
    public:
        string name;
        ComponentBase(string name);
        virtual void input(ComponentBase *component);
        virtual Signal output();
};

// class for inputs connections to the diagram (takes no inputs)
class Input: public ComponentBase {
    private:
        Signal _output = Signal();
    public:
      Input(string name, bool sourceValue);
      virtual Signal output() override;
};

// base class for all basic logic components
COMPONENT_TEMPLATE
class Component: public ComponentBase {
    public:
        array<ComponentBase *, inputCount> inputs = {nullptr}; // vector of inputs to the components

        Component(string name): ComponentBase(name) {};
        virtual Signal output() override; // virtual output function for all subclasses to implement
        virtual void input(ComponentBase *source) override;
};

// perform AND boolean operation
class AndGate: public Component<2> {
    public:
        AndGate(string name): Component(name) {}
        virtual Signal output() override;
};

// perform NOT boolean operation
class NotGate: public Component<1> {
    public:
        NotGate(string name): Component(name) {};
        virtual Signal output() override;
        // virtual ;
};

// perform NAND boolean operation
class NandGate: public Component<2> {
    public:
        NandGate(string name): Component(name) {}
        virtual Signal output() override;
};

// perform OR boolean operation
class OrGate: public Component<2> {
    public:
        OrGate(string name): Component(name) {}
        virtual Signal output() override;
};

// perform NOR boolean operation
class NorGate: public Component<2> {
    public:
        NorGate(string name): Component(name) {}
        virtual Signal output() override;
};

// perform XOR boolean operation
class XorGate: public Component<2> {
    public:
        XorGate(string name): Component(name) {}
        virtual Signal output() override;
};
