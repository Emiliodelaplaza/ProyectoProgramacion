#include "ResultsInfo_driver.hpp"

// Constructor predeterminado
ResultsInfo_driver::ResultsInfo_driver()
    : ResultsInfo(), driver(nullptr) {}

// Constructor con parametros
ResultsInfo_driver::ResultsInfo_driver(int resultId, const Driver* driver, const Race* race, int grid, int position, int points)
    : ResultsInfo(resultId, race, grid, position, points), driver(driver) {}