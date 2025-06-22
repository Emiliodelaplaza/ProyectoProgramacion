#include "Team.hpp"

// Constructor predeterminado
Team::Team()
    : teamId(0), name(""), nationality("") {}

// Constructor con parámetros
Team::Team(int teamId, std::string name, std::string nationality)
    : teamId(teamId), name(name), nationality(nationality) {}