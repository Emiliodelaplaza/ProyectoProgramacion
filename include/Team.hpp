#ifndef TEAM_HPP
#define TEAM_HPP

#include <string>

using namespace std;

class Team {
public:
    int teamId;
    string name;
    string nationality;

    Team();  // Constructor predeterminado vacío
    Team(int teamId, string name, string nationality);  // Constructor con parámetros
};

#endif // TEAM_HPP