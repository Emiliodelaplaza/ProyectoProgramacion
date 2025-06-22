#include "ResultsInfo_team.hpp"

// Constructor predeterminado
ResultsInfo_team::ResultsInfo_team()
    : ResultsInfo(), team(nullptr) {}

// Constructor con parametros
ResultsInfo_team::ResultsInfo_team(int resultId, const Team* team, const Race* race, int grid, int position, int points)
    : ResultsInfo(resultId, race, grid, position, points), team(team) {}