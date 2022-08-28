#pragma once

#include <fstream>
#include <string>

#include "gates.hpp"
#include "diagram.hpp"

using namespace std;



void linkComponent(Circuit *circuit, vector<string> *lines, size_t i);

Circuit parseFile(string filename);


// class CircuitParser {
//     private:
//         fstream filestream;
//         // int inputCount
//     public:
//         CircuitParser(string filename);
//         void parseFile(Circuit *circuit);
// };