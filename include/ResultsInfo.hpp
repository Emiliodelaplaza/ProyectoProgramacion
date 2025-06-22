#ifndef RESULTS_INFO_HPP
#define RESULTS_INFO_HPP

#include "Driver.hpp"
#include "Team.hpp"
#include "Race.hpp"
#include <string>

using namespace std;

class ResultsInfo {
protected:
    int resultId;
    const Race* race;
    int grid;
    int position;
    int points;

public:
    // Constructor predeterminado
    ResultsInfo();

    // Constructor con parámetros base
    ResultsInfo(int resultId, const Race* race, int grid, int position, int points);

    // Métodos accesores comunes
    int getResultId() const { return resultId; }
    const Race* getRace() const { return race; }
    int getGrid() const { return grid; }
    int getPosition() const { return position; }
    int getPoints() const { return points; }
};

#endif // RESULTS_INFO_HPP