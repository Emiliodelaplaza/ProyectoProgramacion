#ifndef RESULTS_INFO_DRIVER_HPP
#define RESULTS_INFO_DRIVER_HPP

#include "ResultsInfo.hpp"
#include "Driver.hpp"

class ResultsInfo_driver : public ResultsInfo {
private:
    const Driver* driver;

public:
    // Constructores
    ResultsInfo_driver();
    ResultsInfo_driver(int resultId, const Driver* driver, const Race* race, int grid, int position, int points);

    // Metodos especificos para driver
    const Driver* getDriver() const { return driver; }
};

#endif // RESULTS_INFO_DRIVER_HPP