#include <iostream>
#include <vector>

#include "gates.hpp"
#include "diagram.hpp"
#include "parser.hpp"

using namespace std;





int main() {

    Circuit circuit;

    parseFile("example.txt", &circuit);

    for (signal output: circuit.outputs) {
        cout << "value: " << output.value << ", voltage: " << output.voltage << endl;
    }

    // LogicSource in1(1);
    // LogicSource in2(0);
    // NotGate reverse;
    // AndGate combine;

    // combine.input(&in1);
    // reverse.input(&in2);
    // combine.input(&reverse);


    // cout << in1.output().value << " " << in2.output().value << endl;
    // cout << "| " << reverse.output().value  << endl;
    // cout << "\\ /" << endl;
    // cout << " " << combine.output().value << endl;

    // cout << combine.output().value << endl;
}