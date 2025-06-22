#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>

using namespace std;

class Circuit {
public:
    int circuitId;
    string name;
    string location;
    string country;

    // Constructor declarado aquí.
    Circuit();

    Circuit(int id, string n, string loc, string country);
};

#endif // CIRCUIT_HPP