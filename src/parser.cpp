
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

#include "gates.hpp"
#include "diagram.hpp"
#include "parser.hpp"

using namespace std;


// link the output of a component to the currently selected one
// circuit should have the celected component be the components vector
// `lines` should point to an argument to the current action (creation of a component)
// i is simply the current iteration number in the calling loop
template <typename componentType>
size_t addComponent(Circuit *circuit, vector<string> *lines, size_t i) {
    // ensure that template type is a subclass of ComponentBase
    static_assert(is_base_of<ComponentBase, componentType>::value, "foreign class template used for addComopnent()");

    // auto _lines = *lines;
    size_t _i = i;
    string name = lines->at(_i); // get the name of the component
    circuit->components.insert( // insert the component
        pair<string, ComponentBase *> ( // of pair type
            name, // with name
            new componentType(name) // to a new component type object
        )
    );
    // *i--;
    // i; // step backward

    string type = lines->at(_i-1); // to get the gate type
    _i++; // step forward to first input
    if(type == "not") {
        // _i++;
        ComponentBase *input = circuit->components.at(lines->at(_i));
        auto compointer = circuit->components.at(name);
        // cout << type(compointer) << endl;
        compointer->input(input);
        // _i++;
        return _i;
    }else {
        auto input2 = vector<string> {"and", "nand", "or", "nor", "xor"};
        if (find(input2.begin(), input2.end(), type) != input2.end()) {
            // _i++;
            ComponentBase *input = circuit->components.at(lines->at(_i));
            circuit->components.at(name)->input(input);
            _i++;
            input = circuit->components.at(lines->at(_i));
            circuit->components.at(name)->input(input);
            // _i++;
            return _i;
        }else {
            throw runtime_error("unrecognized gate type entered");
        }
    }

    i++;
    throw runtime_error("this point of the function should be unreachable");
}

// function that takes a filename and parses it into the given circuit pointer
Circuit parseFile(string filename) {
    Circuit circuit(filename, false);
    fstream filestream = fstream(filename);
    vector<string> lines;
    { // seperate variables and logic for less clutter
        string line;
        // filestream >> line;
        do {
            filestream >> line;
            lines.push_back(line);
        }while(filestream.peek() != EOF);
    }
    // iterate through all the lines read by the file
    for (size_t i = 0; i < lines.size(); i++) {
        // if (lines[i] == "inputs") {
        //     i++;
        //     circuit->inputCount = stoi(lines[i]);
        //     // this increments the counter and sets the max number of inputs
        // }else 
        if (lines[i] == "input") {
            i++;
            // check if circuit has available input space
            // if (circuit->inputs.size() < circuit->inputCount) {
                // set the value of the input the that of the next line read (1 or 0)
            // circuit->inputs.push_back(LogicSource(stoi(lines[i])));
            string name = "_in"+lines[i];
            i++;
            circuit.components.insert( // insert a new component
                pair<string, ComponentBase *>( // of pair type
                    name,
                    new Input(
                        name,
                        stoi(lines[i])
                    )
                )
            );
            // i++;
        }else if (lines[i] == "gate") {
            i++;
            if (lines[i] == "not") {
                i++;
                i = addComponent<NotGate>(&circuit, &lines, i);
                // circuit.components[lines[]].
            }else if(lines[i] == "and") {
                i++;
                i = addComponent<AndGate>(&circuit, &lines, i);
                // circuit->components.push_back(
                //     NamedLogicGate{
                //         lines[i],
                //         new AndGate()
                //     }
                // );
                // i++;
                // linkComponent(circuit, &lines, i);
                // i++;
                // linkComponent(circuit, &lines, i);
            }else if(lines[i] == "nand") {
                i++;
                i = addComponent<NandGate>(&circuit, &lines, i);
                // circuit->components.push_back(
                //     NamedLogicGate{
                //         lines[i],
                //         new NandGate()
                //     }
                // );
                // i++;
                // linkComponent(circuit, &lines, i);
                // i++;
                // linkComponent(circuit, &lines, i);
            }else if(lines[i] == "or") {
                i++;
                i = addComponent<OrGate>(&circuit, &lines, i);
                // i++;
                // circuit->components.push_back(
                //     NamedLogicGate{
                //         lines[i],
                //         new OrGate()
                //     }
                // );
                // i++;
                // linkComponent(circuit, &lines, i);
                // i++;
                // linkComponent(circuit, &lines, i);
            }else if(lines[i] == "nor") {
                i++;
                i = addComponent<NorGate>(&circuit, &lines, i);
                // circuit->components.push_back(
                //     NamedLogicGate{
                //         lines[i],
                //         new NorGate()
                //     }
                // );
                // i++;
                // linkComponent(circuit, &lines, i);
                // i++;
                // linkComponent(circuit, &lines, i);
            }else if(lines[i] == "xor") {
                i++;
                i = addComponent<XorGate>(&circuit, &lines, i);
                // circuit->components.push_back(
                //     NamedLogicGate{
                //         lines[i],
                //         new XorGate()
                //     }
                // );
                // i++;
                // linkComponent(circuit, &lines, i);
                // i++;
                // linkComponent(circuit, &lines, i);
            }else {
                throw runtime_error("Invalid gate name parsed");
            }
        }else if (lines[i] == "output") {
            i++;
            // circuit
            // i++;
            string tmp = lines[i];
            circuit.input(
                circuit.components.at(lines[i])
            );
            // i++;
        }else {
            throw runtime_error("invalid statement parsed");
        }
    }
    return circuit;
}
