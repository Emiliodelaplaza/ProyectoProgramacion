#ifndef RESULTS_INFO_TEAM_HPP
#define RESULTS_INFO_TEAM_HPP

#include "ResultsInfo.hpp"
#include "Team.hpp"

class ResultsInfo_team : public ResultsInfo {
private:
    const Team* team;

public:
    // Constructores
    ResultsInfo_team();
    ResultsInfo_team(int resultId, const Team* team, const Race* race, int grid, int position, int points);

    // Metodos especificos para team
    const Team* getTeam() const { return team; }
};

#endif // RESULTS_INFO_TEAM_HPP