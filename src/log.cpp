
#include <iostream>

#include "parser.hpp"


using namespace std;


void logCircuitOutput(Circuit *circuit) {
    // for (auto output: circuit->outputs) {
    //     cout << "value: " << output.value << ", voltage: " << output.voltage << endl;
    // }
    for (unsigned int i = 0; i < circuit->outputs.size(); i++) {
        shared_ptr<wire> output = circuit->outputs.at(i);
        cout << "value: " << output->value  << ", voltage: " << output->voltage << endl;
    }
}

