#ifndef DRIVING_ANALYSIS_HPP
#define DRIVING_ANALYSIS_HPP

#include <string>
#include <vector>
#include <map>
#include "Driver.hpp"
#include "ResultsInfo_driver.hpp"
#include "Race.hpp"
#include "Team.hpp"
#include "TeamStandings.hpp"

using namespace std;

class DrivingAnalysis {
public:
    // En DrivingAnalysis.hpp
    vector<pair<Driver, map<string, double>>> calculateTopDrivers(int startYear, int endYear, 
        const map<int, Driver>& drivers, 
        const map<int, ResultsInfo_driver>& results,  // Cambiado
        const map<int, Race>& races);
    void saveDriverStatsToFile(const vector<pair<Driver, map<string, double>>>& driverStats, const string& filename);
    void printDriverStats(const vector<pair<Driver, map<string, double>>>& driverStats);
    vector<pair<Team, map<string, double>>> calculateTopTeams(int startYear, int endYear, const map<int, Team>& teams,
        const map<int, TeamStandings>& teamStandings, const map<int, Race>& races);
    void printTeamStats(const vector<pair<Team, map<string, double>>>& teamStats);
    void saveTeamStatsToFile(const vector<pair<Team, map<string, double>>>& teamStats, const string& filename);

private:
    map<string, double> calculateDriverStats(int startYear, int endYear, const Driver& driver,
        const map<int, ResultsInfo_driver>& results, const map<int, Race>& races);
};

#endif // DRIVING_ANALYSIS_HPP