#include "Circuit.hpp"

// Default constructor for Circuit class
Circuit::Circuit()
    : circuitId(0), name(""), location(""), country("") {}

// Parameterized constructor for Circuit class
Circuit::Circuit(int id, string n, string loc, string country)
    : circuitId(id), name(n), location(loc), country(country) {}
