#include "TeamStandings.hpp"

TeamStandings::TeamStandings()
    : teamStandingsId(0), race(nullptr), team(nullptr), points(0), position(0), winsNumber(0) {}

TeamStandings::TeamStandings(int teamStandingsId, const Race* race, const Team* team, int points, int position, int winsNumber)
    : teamStandingsId(teamStandingsId), race(race), team(team), points(points), position(position), winsNumber(winsNumber) {}