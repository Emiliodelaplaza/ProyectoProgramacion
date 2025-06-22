#ifndef TEAM_STANDINGS_HPP
#define TEAM_STANDINGS_HPP

#include "Team.hpp"
#include "Race.hpp"

class TeamStandings {
public:
    int teamStandingsId;
    const Race* race;         // Debe ser const
    const Team* team;     // Debe ser const
    int points;
    int position;
    int winsNumber;

    TeamStandings();
    TeamStandings(int teamStandingsId, const Race* race, const Team* team, int points, int position, int winsNumber);
};

#endif // TEAM_STANDINGS_HPP