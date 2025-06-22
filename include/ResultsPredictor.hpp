#ifndef RESULTS_PREDICTOR_HPP
#define RESULTS_PREDICTOR_HPP

#include <string>
#include <map>
#include <vector>
#include "Driver.hpp"
#include "DriverStandings.hpp"
#include "Race.hpp"
#include "Team.hpp"
#include "TeamStandings.hpp"
#include "ResultsInfo_driver.hpp"
#include "ResultsInfo_team.hpp"

using namespace std;

class ResultsPredictor {
private:
    double calculatePearsonCorrelation(const vector<int>& x, const vector<int>& y);
    
public:
    void predictResults(const map<int, Driver>& drivers, const map<int, DriverStandings>& standings, const map<int, Race>& races, const string& circuitName = "");
    void predictTeamResults(const map<int, Team>& teams, const map<int, TeamStandings>& standings, const map<int, Race>& races, const string& circuitName = "");
    void calculateStartPositionImpact(const map<int, ResultsInfo_driver>& driverResults, const map<int, ResultsInfo_team>& teamResults);
};

#endif // RESULTS_PREDICTOR_HPP