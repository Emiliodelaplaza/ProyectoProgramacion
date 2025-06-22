#include "Race.hpp"

// Constructor predeterminado
Race::Race()
    : raceId(0), year(0), circuit(nullptr), name(""), date("") {}

// Constructor con parámetros
Race::Race(int raceId, int year, const Circuit* circuit, std::string name, std::string date)
    : raceId(raceId), year(year), circuit(circuit), name(name), date(date) {}