#pragma once

#include <fstream>
#include <string>

#include "gates.hpp"
#include "diagram.hpp"

using namespace std;



void linkComponent(Circuit *circuit, vector<string> *lines, unsigned int i);

void parseFile(string filename, Circuit *circuit);


// class CircuitParser {
//     private:
//         fstream filestream;
//         // int inputCount
//     public:
//         CircuitParser(string filename);
//         void parseFile(Circuit *circuit);
// };