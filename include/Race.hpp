#ifndef RACE_HPP
#define RACE_HPP

#include "Circuit.hpp"
#include <string>

using namespace std;

class Race {
public:
    int raceId;
    int year;
    const Circuit* circuit;  // Cambio a puntero a const
    string name;
    string date;

    Race();  // Constructor predeterminado
    Race(int raceId, int year, const Circuit* circuit, string name, string date);
};

#endif // RACE_HPP