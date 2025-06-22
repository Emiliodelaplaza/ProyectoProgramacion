#include "DataManager.hpp"

map<int, Circuit> DataManager::loadCircuits(const string& filename) {
    CSVReader reader;
    map<int, Circuit> circuits;
    vector<vector<string>> data = reader.readCSV(filename);

    for (size_t i = 1; i < data.size(); ++i) {
        const auto& row = data[i];
        if (row.size() >= 4) {
            try {
                int id = stoi(row[0]);
                string name = row[2];
                string location = row[3];
                string country = row[4];
                circuits[id] = Circuit(id, name, location, country);
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid argument when converting string to int: " << e.what() << endl;
            } catch (const out_of_range& e) {
                cerr << "Error: String value out of integer range: " << e.what() << endl;
            }
        }
    }

    return circuits;
}

map<int, Race> DataManager::loadRaces(const string& filename, const map<int, Circuit>& circuits) {
    CSVReader reader;
    map<int, Race> races;
    vector<vector<string>> data = reader.readCSV(filename);

    for (size_t i = 1; i < data.size(); ++i) {  // Asumimos que la primera fila son encabezados
        const auto& row = data[i];
        if (row.size() >= 5) {
            int raceId = stoi(row[0]);
            int year = stoi(row[1]);
            int circuitId = stoi(row[3]);
            string name = row[4];
            string date = row[5];
            const Circuit* circuitPtr = nullptr;  // Cambiado a const Circuit*

            if (circuits.find(circuitId) != circuits.end()) {
                circuitPtr = &circuits.at(circuitId);
            }

            races[raceId] = Race(raceId, year, circuitPtr, name, date);
        }
    }

    return races;
}

map<int, Driver> DataManager::loadDrivers(const string& filename) {
    CSVReader reader;
    map<int, Driver> drivers;
    vector<vector<string>> data = reader.readCSV(filename);

    for (size_t i = 1; i < data.size(); ++i) {  // Asumimos que la primera fila son encabezados
        const auto& row = data[i];
        if (row.size() >= 7) {
            int driverId = stoi(row[0]);
            string code = row[3];
            string fullName = row[4] + " " + row[5]; // Assuming first name and last name are split
            string dob = row[6];
            string nationality = row[7];
            drivers[driverId] = Driver(driverId, code, fullName, dob, nationality);
        }
    }

    return drivers;
}

map<int, Team> DataManager::loadTeams(const string& filename) {
    CSVReader reader;
    map<int, Team> teams;
    vector<vector<string>> data = reader.readCSV(filename);

    for (size_t i = 1; i < data.size(); ++i) {  // Asumiendo que la primera fila son encabezados
        const auto& row = data[i];
        if (row.size() >= 3) {
            int constructorId = stoi(row[0]);
            string name = row[2];
            string nationality = row[3];
            teams[constructorId] = Team(constructorId, name, nationality);
        }
    }

    return teams;
}

map<int, DriverStandings> DataManager::loadDriverStandings(const string& filename, const map<int, Race>& races, const map<int, Driver>& drivers) {
    CSVReader reader;
    map<int, DriverStandings> standings;
    vector<vector<string>> data = reader.readCSV(filename);

    for (size_t i = 1; i < data.size(); ++i) {
        const auto& row = data[i];
        if (row.size() >= 6) {
            int driverStandingsId = stoi(row[0]);
            int raceId = stoi(row[1]);
            int driverId = stoi(row[2]);
            int points = stoi(row[3]);
            int position = stoi(row[4]);
            int winsNumber = stoi(row[6]);

            const Race* race = races.count(raceId) ? &races.at(raceId) : nullptr;
            const Driver* driver = drivers.count(driverId) ? &drivers.at(driverId) : nullptr;

            standings[driverStandingsId] = DriverStandings(driverStandingsId, race, driver, points, position, winsNumber);
        }
    }

    return standings;
}

map<int, TeamStandings> DataManager::loadTeamStandings(const string& filename, const map<int, Race>& races, const map<int, Team>& teams) {
    CSVReader reader;
    map<int, TeamStandings> standings;
    vector<vector<string>> data = reader.readCSV(filename);
    for (size_t i = 1; i < data.size(); ++i) {
        const auto& row = data[i];
        if (row.size() >= 6) {
            int teamStandingsId = stoi(row[0]);
            int raceId = stoi(row[1]);
            int teamId = stoi(row[2]);
            int points = stoi(row[3]);
            int position = stoi(row[4]);
            int winsNumber = stoi(row[6]);

            const Race* race = races.count(raceId) ? &races.at(raceId) : nullptr;
            const Team* team = teams.count(teamId) ? &teams.at(teamId) : nullptr;

            standings[teamStandingsId] = TeamStandings(teamStandingsId, race, team, points, position, winsNumber);
        }
    }

    return standings;
}




map<int, ResultsInfo_driver> DataManager::loadDriverResults(const string& filename, const map<int, Driver>& drivers, const map<int, Race>& races) {
    CSVReader reader;
    map<int, ResultsInfo_driver> results;
    vector<vector<string>> data = reader.readCSV(filename);

    for (size_t i = 1; i < data.size(); ++i) {
        const auto& row = data[i];
        if (row.size() >= 10) {
            if (row[1] == "\\N" || row[2] == "\\N" || row[5] == "\\N" || row[6] == "\\N" || row[9] == "\\N") {
                continue;
            }

            int resultId = stoi(row[0]);
            int raceId = stoi(row[1]);
            int driverId = stoi(row[2]);
            int grid = stoi(row[5]);
            int position = stoi(row[6]);
            int points = stoi(row[9]);

            const Driver* driver = drivers.count(driverId) ? &drivers.at(driverId) : nullptr;
            const Race* race = races.count(raceId) ? &races.at(raceId) : nullptr;

            if (driver && race) {
                results[resultId] = ResultsInfo_driver(resultId, driver, race, grid, position, points);
            }
        }
    }

    return results;
}

map<int, ResultsInfo_team> DataManager::loadTeamResults(const string& filename, const map<int, Team>& teams, const map<int, Race>& races) {
    CSVReader reader;
    map<int, ResultsInfo_team> results;
    vector<vector<string>> data = reader.readCSV(filename);

    for (size_t i = 1; i < data.size(); ++i) {
        const auto& row = data[i];
        if (row.size() >= 10) {
            if (row[1] == "\\N" || row[3] == "\\N" || row[5] == "\\N" || row[6] == "\\N" || row[9] == "\\N") {
                continue;
            }

            int resultId = stoi(row[0]);
            int raceId = stoi(row[1]);
            int teamId = stoi(row[3]);
            int grid = stoi(row[5]);
            int position = stoi(row[6]);
            int points = stoi(row[9]);

            const Team* team = teams.count(teamId) ? &teams.at(teamId) : nullptr;
            const Race* race = races.count(raceId) ? &races.at(raceId) : nullptr;

            if (team && race) {
                results[resultId] = ResultsInfo_team(resultId, team, race, grid, position, points);
            }
        }
    }

    return results;
}