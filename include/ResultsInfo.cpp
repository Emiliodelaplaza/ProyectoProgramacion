#include "ResultsInfo.hpp"

// Constructor predeterminado
ResultsInfo::ResultsInfo()
    : resultId(0), race(nullptr), grid(0), position(0), points(0) {}

// Constructor con parámetros base
ResultsInfo::ResultsInfo(int resultId, const Race* race, int grid, int position, int points)
    : resultId(resultId), race(race), grid(grid), position(position), points(points) {}