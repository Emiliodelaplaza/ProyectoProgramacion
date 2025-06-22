#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP

#include <map>
#include <string>
#include <iostream>
#include "Circuit.hpp"
#include "Race.hpp"
#include "Driver.hpp"
#include "Team.hpp"
#include "TeamStandings.hpp"
#include "DriverStandings.hpp"
#include "ResultsInfo_driver.hpp"
#include "ResultsInfo_team.hpp"
#include "CSVReader.hpp"

using namespace std;

class DataManager {
public:
    map<int, Circuit> loadCircuits(const string& filename);
    map<int, Race> loadRaces(const string& filename, const map<int, Circuit>& circuits);
    map<int, Driver> loadDrivers(const string& filename);
    map<int, Team> loadTeams(const string& filename);
    map<int, DriverStandings> loadDriverStandings(const string& filename, const map<int, Race>& races, const map<int, Driver>& drivers);
    map<int, TeamStandings> loadTeamStandings(const string& filename, const map<int, Race>& races, const map<int, Team>& teams);
    map<int, ResultsInfo_driver> loadDriverResults(const string& filename, const map<int, Driver>& drivers, const map<int, Race>& races);
    map<int, ResultsInfo_team> loadTeamResults(const string& filename, const map<int, Team>& teams, const map<int, Race>& races);
};

#endif //DATAMANAGER_HPP