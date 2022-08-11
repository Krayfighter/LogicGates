
#include <iostream>

#include "parser.hpp"


using namespace std;


void logCircuitOutput(Circuit *circuit) {
    for (signal output: circuit->outputs) {
        cout << "value: " << output.value << ", voltage: " << output.voltage << endl;
    }
}

