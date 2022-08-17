
#include <fstream>
#include <string>

#include "gates.hpp"
#include "diagram.hpp"
#include "parser.hpp"

using namespace std;


// link the output of a component to the currently selected one
// circuit should have the celected component be the components vector
// `lines` should point to an argument to the current action (creation of a component)
// i is simply the current iteration number in the calling loop
void linkComponent(Circuit *circuit, vector<string> *lines, unsigned int i) {
    if (lines->at(i)[0] == '_') { // if the current line start with '_' it is handled as a circuit input
        string snum = lines->at(i); // store the current line
        string _snum; // output of following statements
        for(unsigned int iter = 3; iter < snum.size(); iter++) { // start loop after the text of `_in`
            _snum += snum[iter]; // add the current character (number character) to `_snum`
        }
        int inum = stoi(_snum);
        circuit->components[ // get the latest member of circuit's components
            circuit->components.size()-1
        ].gate->input( // give its gate the input of previously obtained input number (snum)
            circuit->inputs[inum].getValue()
        );
    }else { // the input to the current component is the output of another
        LogicGate *gate = circuit->searchGate(lines->at(i)); // search for the input gate by name
        circuit->components[ // get the current component
            circuit->components.size()-1
        ].gate->input(gate->output()); // set its input the the selected gate's output
    }
}

// function that takes a filename and parses it into the given circuit pointer
void parseFile(string filename, Circuit *circuit) {
    fstream filestream = fstream(filename);
    vector<string> lines;
    { // seperate variables and logic for less clutter
        string line;
        string old;
        filestream >> line;
        while(line != old) {
            lines.push_back(line);
            old = line;
            filestream >> line;
        }
    }
    // iterate through all the lines read by the file
    for (unsigned int i = 0; i < lines.size(); i++) {
        if (lines[i] == "inputs") {
            i++;
            circuit->inputCount = stoi(lines[i]);
            // this increments the counter and sets the max number of inputs
        }else if (lines[i] == "addin") {
            i++;
            // check if circuit has available input space
            if (circuit->inputs.size() < circuit->inputCount) {
                // set the value of the input the that of the next line read (1 or 0)
                circuit->inputs.push_back(LogicSource(stoi(lines[i])));
            }else {
                // throw an error if more inputs are added than should be
                throw runtime_error("Too many input values parsed");
            }
        }else if (lines[i] == "gate") {
            i++;
            if (lines[i] == "not") {
                i++;
                circuit->components.push_back(
                    NamedLogicGate{
                        lines[i],
                        new NotGate()
                    }
                ); // adds a NotGate the the Circuit
                i++;
                linkComponent(circuit, &lines, i);
                // increments the counter to the argument for this action
                // then calls linkComponent with the circuit pointer, lines poinrter
                // and the counter number
            }else if(lines[i] == "and") {
                i++;
                circuit->components.push_back(
                    NamedLogicGate{
                        lines[i],
                        new AndGate()
                    }
                );
                i++;
                linkComponent(circuit, &lines, i);
                i++;
                linkComponent(circuit, &lines, i);
            }else if(lines[i] == "nand") {
                i++;
                circuit->components.push_back(
                    NamedLogicGate{
                        lines[i],
                        new NandGate()
                    }
                );
                i++;
                linkComponent(circuit, &lines, i);
                i++;
                linkComponent(circuit, &lines, i);
            }else if(lines[i] == "or") {
                i++;
                circuit->components.push_back(
                    NamedLogicGate{
                        lines[i],
                        new OrGate()
                    }
                );
                i++;
                linkComponent(circuit, &lines, i);
                i++;
                linkComponent(circuit, &lines, i);
            }else if(lines[i] == "nor") {
                i++;
                circuit->components.push_back(
                    NamedLogicGate{
                        lines[i],
                        new NorGate()
                    }
                );
                i++;
                linkComponent(circuit, &lines, i);
                i++;
                linkComponent(circuit, &lines, i);
            }else if(lines[i] == "xor") {
                i++;
                circuit->components.push_back(
                    NamedLogicGate{
                        lines[i],
                        new XorGate()
                    }
                );
                i++;
                linkComponent(circuit, &lines, i);
                i++;
                linkComponent(circuit, &lines, i);
            }else {
                throw runtime_error("Invalid gate name parsed");
            }
        }else if (lines[i] == "output") {
            i++;
            // increment the counter to point to this actions argument
            // then search for it in the circuits components vector
            LogicGate *gate = circuit->searchGate(lines[i]);
            // then push its output onto the circuits output vector
            circuit->outputs.push_back(gate->output());
        }else {
            throw runtime_error("invalid statement parsed");
        }
    }
}
