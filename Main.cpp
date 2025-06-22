#include <iostream>
#include <fstream>
#include <limits>
#include "include/DataManager.hpp"
#include "include/ResultsPredictor.hpp"
#include "include/DrivingAnalysis.hpp"
#include "include/StrategyRecommendation.hpp"
#include <map>
#include <stdexcept>

using namespace std;

// Excepcion de fallos con cargar los datos
class FileLoadException : public runtime_error {
public:
    FileLoadException(const string& filename, const string& details = "")
        : runtime_error("Error al cargar el archivo: " + filename + 
                      (details.empty() ? "" : ". Detalles: " + details)) {}
};

// Excepcion de seleccion de opciones invalidas
class InvalidOptionException : public runtime_error {
public:
    InvalidOptionException(const string& input = "")
        : runtime_error("Opcion no valida" + 
                       (input.empty() ? "" : ": " + input) + 
                       ". Por favor intente nuevamente.") {}
};

// Excepcion rango de anos invalido
class InvalidYearException : public invalid_argument {
public:
    InvalidYearException(int start, int end)
        : invalid_argument("Ano de inicio (" + to_string(start) + 
                          ") no puede ser mayor al ano final (" + 
                          to_string(end) + ")") {}
};

// Error de respuesta en campo

class InvalidInputException : public runtime_error {
public:
    InvalidInputException(const string& field)
        : runtime_error("Entrada invalida para el campo: " + field) {}
};

// Datos vacíos
class EmptyDataException : public runtime_error {
public:
    EmptyDataException(const string& datasetName)
        : runtime_error("El conjunto de datos esta vacio: " + datasetName) {}
};


// Comprobacion de la existencia del archivo de los datos
bool fileExists(const string& filename) {
    ifstream testFile(filename);
    return testFile.good();
}

// Comprobacion rango de anos valido
void validateYearInput(int year) {
    if (cin.fail() || year < 1950 || year > 2023) { // Ajusta el rango segun tus datos
        throw InvalidInputException("ano - debe ser entre 1950 y 2023");
    }
}

int main() {
    DataManager dataManager;
    ResultsPredictor predictor;
    DrivingAnalysis analysis;
    StrategyRecommendation strategy;

    try {
        // Configuracion de rutas de archivos
        string circuitsFilename = "Database/circuits.csv";
        string racesFilename = "Database/races.csv";
        string driverFilename = "Database/drivers.csv";
        string driverStandingsFilename = "Database/driver_standings.csv";
        string teamFilename = "Database/constructors.csv";
        string teamStandingsFilename = "Database/constructor_standings.csv";
        string resultsInfoFilename = "Database/results.csv";

        // Verificar existencia de archivos
        if (!fileExists(circuitsFilename)) throw FileLoadException(circuitsFilename, "Archivo no encontrado");
        if (!fileExists(racesFilename)) throw FileLoadException(racesFilename, "Archivo no encontrado");
        if (!fileExists(driverFilename)) throw FileLoadException(driverFilename, "Archivo no encontrado");
        if (!fileExists(driverStandingsFilename)) throw FileLoadException(driverStandingsFilename, "Archivo no encontrado");
        if (!fileExists(teamFilename)) throw FileLoadException(teamFilename, "Archivo no encontrado");
        if (!fileExists(teamStandingsFilename)) throw FileLoadException(teamStandingsFilename, "Archivo no encontrado");
        if (!fileExists(resultsInfoFilename)) throw FileLoadException(resultsInfoFilename, "Archivo no encontrado");

        // Declaracion de estructuras de datos
        map<int, Circuit> circuits;
        map<int, Race> races;
        map<int, Driver> drivers;
        map<int, Team> teams;
        map<int, DriverStandings> standings;
        map<int, TeamStandings> teamStandings;
        map<int, ResultsInfo_driver> driverResults;
        map<int, ResultsInfo_team> teamResults;

        // Carga de datos con manejo de excepciones
        try {
            circuits = dataManager.loadCircuits(circuitsFilename);
            if (circuits.empty()) throw EmptyDataException("circuitos");
            
            races = dataManager.loadRaces(racesFilename, circuits);
            if (races.empty()) throw EmptyDataException("carreras");
            
            drivers = dataManager.loadDrivers(driverFilename);
            if (drivers.empty()) throw EmptyDataException("conductores");
            
            teams = dataManager.loadTeams(teamFilename);
            if (teams.empty()) throw EmptyDataException("equipos");
            
            standings = dataManager.loadDriverStandings(driverStandingsFilename, races, drivers);
            if (standings.empty()) throw EmptyDataException("clasificacion de conductores");
            
            teamStandings = dataManager.loadTeamStandings(teamStandingsFilename, races, teams);
            if (teamStandings.empty()) throw EmptyDataException("clasificacion de equipos");
            
            driverResults = dataManager.loadDriverResults(resultsInfoFilename, drivers, races);
            if (driverResults.empty()) throw EmptyDataException("resultados de conductores");
            
            teamResults = dataManager.loadTeamResults(resultsInfoFilename, teams, races);
            if (teamResults.empty()) throw EmptyDataException("resultados de equipos");
        }
        catch (const exception& e) {
            throw FileLoadException("Error al cargar datos", e.what());
        }

        // Bucle principal del menu
        while (true) {
            cout << "\n--- Menu Principal ---\n";
            cout << "1. Prediccion de resultados para conductores\n";
            cout << "2. Prediccion de resultados para equipos\n";
            cout << "3. Predecir importancia de la posicion de salida\n";
            cout << "4. Analisis de top 5 conductores\n";
            cout << "5. Generar reporte de top 5 conductores\n";
            cout << "6. Analisis de top 5 equipos\n";
            cout << "7. Generar reporte de top 5 equipos\n";
            cout << "8. Recomendacion de estrategia de pits y neumaticos\n";
            cout << "9. Recomendacion de estrategia de combustible\n";
            cout << "10. Recomendacion de configuracion del coche\n";
            cout << "11. Salir\n";
            cout << "Elija una opcion: ";

            int choice;
            try {
                cin >> choice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw InvalidInputException("opcion del menu");
                }
                cin.ignore();

                switch (choice) {
                case 1: { // Prediccion de resultados para conductores
                    cout << "\n1. Prediccion general\n";
                    cout << "2. Prediccion por circuito\n";
                    cout << "Elija una opcion para la prediccion: ";
                    
                    int subChoice;
                    cin >> subChoice;
                    if (cin.fail() || (subChoice != 1 && subChoice != 2)) {
                        throw InvalidOptionException(to_string(subChoice));
                    }
                    cin.ignore();

                    if (subChoice == 1) {
                        predictor.predictResults(drivers, standings, races);
                    } else {
                        string circuitName;
                        cout << "Ingrese el nombre del circuito: ";
                        getline(cin, circuitName);
                        if (circuitName.empty()) {
                            throw InvalidInputException("nombre del circuito");
                        }
                        
                        bool circuitFound = false;
                        for (const auto& circuit : circuits) {
                            if (circuit.second.name == circuitName) {
                                circuitFound = true;
                                break;
                            }
                        }
                        if (!circuitFound) {
                            throw InvalidInputException("nombre del circuito - circuito no encontrado");
                        }
                        
                        predictor.predictResults(drivers, standings, races, circuitName);
                    }
                    break;
                }
                case 2: { // Prediccion de resultados para equipos
                    cout << "\n1. Prediccion general\n";
                    cout << "2. Prediccion por circuito\n";
                    cout << "Elija una opcion para la prediccion: ";
                    
                    int subChoice;
                    cin >> subChoice;
                    if (cin.fail() || (subChoice != 1 && subChoice != 2)) {
                        throw InvalidOptionException(to_string(subChoice));
                    }
                    cin.ignore();

                    if (subChoice == 1) {
                        predictor.predictTeamResults(teams, teamStandings, races);
                    } else {
                        string circuitName;
                        cout << "Ingrese el nombre del circuito: ";
                        getline(cin, circuitName);
                        if (circuitName.empty()) {
                            throw InvalidInputException("nombre del circuito");
                        }
                        
                        bool circuitFound = false;
                        for (const auto& circuit : circuits) {
                            if (circuit.second.name == circuitName) {
                                circuitFound = true;
                                break;
                            }
                        }
                        if (!circuitFound) {
                            throw InvalidInputException("nombre del circuito - circuito no encontrado");
                        }
                        
                        predictor.predictTeamResults(teams, teamStandings, races, circuitName);
                    }
                    break;
                }
                case 3: // Importancia de la posicion de salida
                    predictor.calculateStartPositionImpact(driverResults, teamResults);
                    break;
                case 4: { // Analisis de top 5 conductores
                    int startYear, endYear;
                    cout << "Ingrese ano de inicio: ";
                    cin >> startYear;
                    validateYearInput(startYear);
                    
                    cout << "Ingrese ano final: ";
                    cin >> endYear;
                    validateYearInput(endYear);
                    cin.ignore();

                    if (startYear > endYear) {
                        throw InvalidYearException(startYear, endYear);
                    }

                    auto topDrivers = analysis.calculateTopDrivers(startYear, endYear, drivers, driverResults, races);
                    analysis.printDriverStats(topDrivers);
                    break;
                }
                case 5: { // Generar reporte de top 5 conductores
                    string filename;
                    int startYear, endYear;
                    
                    cout << "Ingrese nombre del archivo para guardar el reporte: ";
                    getline(cin, filename);
                    if (filename.empty()) {
                        throw InvalidInputException("nombre de archivo");
                    }
                    
                    cout << "Ingrese ano de inicio: ";
                    cin >> startYear;
                    validateYearInput(startYear);
                    
                    cout << "Ingrese ano final: ";
                    cin >> endYear;
                    validateYearInput(endYear);
                    cin.ignore();

                    if (startYear > endYear) {
                        throw InvalidYearException(startYear, endYear);
                    }

                    auto topDrivers = analysis.calculateTopDrivers(startYear, endYear, drivers, driverResults, races);
                    analysis.saveDriverStatsToFile(topDrivers, filename);
                    cout << "Reporte guardado en '" << filename << "'\n";
                    break;
                }
                case 6: { // Analisis de top 5 equipos
                    int startYear, endYear;
                    cout << "Ingrese ano de inicio: ";
                    cin >> startYear;
                    validateYearInput(startYear);
                    
                    cout << "Ingrese ano final: ";
                    cin >> endYear;
                    validateYearInput(endYear);
                    cin.ignore();

                    if (startYear > endYear) {
                        throw InvalidYearException(startYear, endYear);
                    }

                    auto topTeams = analysis.calculateTopTeams(startYear, endYear, teams, teamStandings, races);
                    analysis.printTeamStats(topTeams);
                    break;
                }
                case 7: { // Generar reporte de top 5 equipos
                    string filename;
                    int startYear, endYear;
                    
                    cout << "Ingrese nombre del archivo para guardar el reporte: ";
                    getline(cin, filename);
                    if (filename.empty()) {
                        throw InvalidInputException("nombre de archivo");
                    }
                    
                    cout << "Ingrese ano de inicio: ";
                    cin >> startYear;
                    validateYearInput(startYear);
                    
                    cout << "Ingrese ano final: ";
                    cin >> endYear;
                    validateYearInput(endYear);
                    cin.ignore();

                    if (startYear > endYear) {
                        throw InvalidYearException(startYear, endYear);
                    }

                    auto topTeams = analysis.calculateTopTeams(startYear, endYear, teams, teamStandings, races);
                    analysis.saveTeamStatsToFile(topTeams, filename);   // Guardamos el reporte
                    cout << "Reporte guardado en '" << filename << "'\n";
                    break;
                }
                case 8: { // Recomendacion de estrategia de pits y neumaticos
                    string weather;
                    int laps;
                    double circuitLength;
                    
                    cout << "Ingrese condiciones climaticas (lluvioso, calor, etc.): ";
                    getline(cin, weather);
                    if (weather.empty()) {
                        throw InvalidInputException("condiciones climaticas");
                    }
                    
                    cout << "Ingrese numero de vueltas: ";
                    cin >> laps;
                    if (cin.fail() || laps <= 0) {
                        throw InvalidInputException("numero de vueltas");
                    }
                    
                    cout << "Ingrese longitud del circuito en km: ";
                    cin >> circuitLength;
                    if (cin.fail() || circuitLength <= 0) {
                        throw InvalidInputException("longitud del circuito");
                    }
                    cin.ignore();

                    cout << "\nRecomendacion de paradas en boxes:\n"
                        << strategy.recommendPitStops(weather, laps, circuitLength)
                        << "\n\nRecomendacion de neumaticos:\n"
                        << strategy.recommendTireType(weather, laps)
                        << endl;
                    break;
                }
                case 9: { // Recomendacion de estrategia de combustible
                    int laps;
                    double circuitLength;
                    string weather;
                    
                    cout << "Ingrese condiciones climaticas (lluvioso, calor, etc.): ";
                    getline(cin, weather);
                    if (weather.empty()) {
                        throw InvalidInputException("condiciones climaticas");
                    }
                    
                    cout << "Ingrese numero de vueltas: ";
                    cin >> laps;
                    if (cin.fail() || laps <= 0) {
                        throw InvalidInputException("numero de vueltas");
                    }
                    
                    cout << "Ingrese longitud del circuito en km: ";
                    cin >> circuitLength;
                    if (cin.fail() || circuitLength <= 0) {
                        throw InvalidInputException("longitud del circuito");
                    }
                    cin.ignore();

                    cout << "\nRecomendacion de estrategia de combustible:\n"
                        << strategy.recommendFuelStrategy(laps, circuitLength, weather)
                        << endl;
                    break;
                }
                case 10: { // Recomendacion de configuracion del coche
                    string circuitType;
                    string weather;
                    
                    cout << "Ingrese tipo de circuito (altaDownforce, altaVelocidad, etc.): ";
                    getline(cin, circuitType);
                    if (circuitType.empty()) {
                        throw InvalidInputException("tipo de circuito");
                    }
                    
                    cout << "Ingrese condiciones climaticas (lluvioso, calor, etc.): ";
                    getline(cin, weather);
                    if (weather.empty()) {
                        throw InvalidInputException("condiciones climaticas");
                    }

                    cout << "\nRecomendacion de configuracion del coche:\n"
                        << strategy.recommendCarSetup(circuitType, weather)
                        << endl;
                    break;
                }
                case 11: // Salir del programa
                    cout << "Saliendo del programa...\n";
                    return 0;
                default:
                    throw InvalidOptionException(to_string(choice));
                }
            }
            catch (const InvalidOptionException& e) {
                cerr << "\nError: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            catch (const InvalidYearException& e) {
                cerr << "\nError: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            catch (const InvalidInputException& e) {
                cerr << "\nError: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            catch (const exception& e) {
                cerr << "\nError inesperado: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    catch (const FileLoadException& e) {
        cerr << "\nError Critico: " << e.what() << endl;
        cerr << "El programa no puede continuar sin los datos necesarios." << endl;
        return 1;
    }
    catch (const EmptyDataException& e) {
        cerr << "\nError Critico: " << e.what() << endl;
        cerr << "El programa no puede continuar con conjuntos de datos vacios." << endl;
        return 1;
    }
    catch (const exception& e) {
        cerr << "\nError Inesperado: " << e.what() << endl;
        return 1;
    }

    return 0;
}