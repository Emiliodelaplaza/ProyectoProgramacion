#include "DrivingAnalysis.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

//Calcula los 5 mejores pilotos según sus puntos medios en un rango de años
vector<pair<Driver, map<string, double>>> DrivingAnalysis::calculateTopDrivers(int startYear, int endYear,
    const map<int, Driver>& drivers,
    const map<int, ResultsInfo_driver>& results,
    const map<int, Race>& races) {
    vector<pair<Driver, map<string, double>>> driverStats;

    for (const auto& driver : drivers) {
        map<string, double> stats = calculateDriverStats(startYear, endYear, driver.second, results, races);
        if (!stats.empty()) {
            driverStats.push_back({ driver.second, stats });
        }
    }

    sort(driverStats.begin(), driverStats.end(), [](const auto& a, const auto& b) {
        return a.second.at("AveragePoints") > b.second.at("AveragePoints");
        });

    if (driverStats.size() > 5) {
        driverStats.resize(5);
    }

    return driverStats;
}

// Calcula estadísticas básicas (max, min, promedio, desviación) de un piloto.
map<string, double> DrivingAnalysis::calculateDriverStats(int startYear, int endYear, const Driver& driver,
    const map<int, ResultsInfo_driver>& results,
    const map<int, Race>& races) {
    vector<double> points;

    for (const auto& result : results) {
        if (result.second.getDriver() && result.second.getDriver()->driverId == driver.driverId) {
            auto raceIt = races.find(result.second.getRace()->raceId);
            if (raceIt != races.end() && raceIt->second.year >= startYear && raceIt->second.year <= endYear) {
                points.push_back(result.second.getPoints());
            }
        }
    }

    if (points.empty()) {
        return {};
    }

    double maxPoints = *max_element(points.begin(), points.end());
    double minPoints = *min_element(points.begin(), points.end());
    double averagePoints = accumulate(points.begin(), points.end(), 0.0) / points.size();
    double sum_sq = inner_product(points.begin(), points.end(), points.begin(), 0.0);
    double stdDevPoints = sqrt(sum_sq / points.size() - averagePoints * averagePoints);

    return { {"MaxPoints", maxPoints}, {"MinPoints", minPoints},
            {"AveragePoints", averagePoints}, {"StdDevPoints", stdDevPoints} };
}

// Guarda las estadísticas de los pilotos en un fichero de texto.
void DrivingAnalysis::saveDriverStatsToFile(const vector<pair<Driver, map<string, double>>>& driverStats, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& item : driverStats) {
            file << "Driver: " << item.first.fullName << "\n";
            file << "DOB: " << item.first.dob << ", Nationality: " << item.first.nationality << "\n";
            file << "Max Points: " << item.second.at("MaxPoints") << ", Min Points: " << item.second.at("MinPoints") << "\n";
            file << "Average Points: " << item.second.at("AveragePoints") << ", Std. Deviation of Points: " << item.second.at("StdDevPoints") << "\n\n";
        }
        file.close();
    }
}

// Muestra por consola las estadísticas de los pilotos.
void DrivingAnalysis::printDriverStats(const vector<pair<Driver, map<string, double>>>& driverStats) {
    for (const auto& item : driverStats) {
        cout << "Driver: " << item.first.fullName << "\n";
        cout << "DOB: " << item.first.dob << ", Nationality: " << item.first.nationality << "\n";
        cout << "Max Points: " << item.second.at("MaxPoints") << ", Min Points: " << item.second.at("MinPoints") << "\n";
        cout << "Average Points: " << item.second.at("AveragePoints") << ", Std. Deviation of Points: " << item.second.at("StdDevPoints") << "\n\n";
    }
}

// Calcula los 5 mejores equipos según puntos medios en un rango de años.
vector<pair<Team, map<string, double>>> DrivingAnalysis::calculateTopTeams(int startYear, int endYear, const map<int, Team>& teams, const map<int, TeamStandings>& teamStandings, const map<int, Race>& races) {
    vector<pair<Team, map<string, double>>> teamStats;

    for (const auto& team : teams) {
        vector<double> points;
        for (const auto& standing : teamStandings) {
            if (standing.second.team->teamId == team.second.teamId && races.at(standing.second.race->raceId).year >= startYear && races.at(standing.second.race->raceId).year <= endYear) {
                points.push_back(standing.second.points);
            }
        }

        if (!points.empty()) {
            double maxPoints = *max_element(points.begin(), points.end());
            double minPoints = *min_element(points.begin(), points.end());
            double averagePoints = accumulate(points.begin(), points.end(), 0.0) / points.size();
            double stdDevPoints = sqrt(inner_product(points.begin(), points.end(), points.begin(), 0.0) / points.size() - averagePoints * averagePoints);
            map<string, double> stats = {{"MaxPoints", maxPoints}, {"MinPoints", minPoints}, {"AveragePoints", averagePoints}, {"StdDevPoints", stdDevPoints}};
            teamStats.push_back({team.second, stats});
        }
    }

    sort(teamStats.begin(), teamStats.end(), [](const auto& a, const auto& b) {
        return a.second.at("AveragePoints") > b.second.at("AveragePoints");
    });

    if (teamStats.size() > 5) {
        teamStats.resize(5);
    }

    return teamStats;
}

// Muestra por consola las estadísticas de equipos.
void DrivingAnalysis::printTeamStats(const vector<pair<Team, map<string, double>>>& teamStats) {
    for (const auto& item : teamStats) {
        cout << "Team: " << item.first.name << "\n";
        cout << "Nationality: " << item.first.nationality << "\n";
        cout << "Max Points: " << item.second.at("MaxPoints") << ", Min Points: " << item.second.at("MinPoints") << "\n";
        cout << "Average Points: " << item.second.at("AveragePoints") << ", Std. Deviation of Points: " << item.second.at("StdDevPoints") << "\n\n";
    }
}

// Guarda estadísticas de equipos en un fichero de texto
void DrivingAnalysis::saveTeamStatsToFile(const vector<pair<Team, map<string, double>>>& teamStats, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& item : teamStats) {
            file << "Team: " << item.first.name << "\n";
            file << "Nationality: " << item.first.nationality << "\n";
            file << "Max Points: " << item.second.at("MaxPoints") << ", Min Points: " << item.second.at("MinPoints") << "\n";
            file << "Average Points: " << item.second.at("AveragePoints") << ", Std. Deviation of Points: " << item.second.at("StdDevPoints") << "\n\n";
        }
        file.close();
    }
}