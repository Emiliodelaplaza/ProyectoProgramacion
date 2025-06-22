#ifndef DRIVER_STANDINGS_HPP
#define DRIVER_STANDINGS_HPP

#include "Driver.hpp"
#include "Race.hpp"

class DriverStandings {
public:
    int driverStandingsId;
    const Race* race;         // Debe ser const
    const Driver* driver;     // Debe ser const
    int points;
    int position;
    int winsNumber;

    DriverStandings();
    DriverStandings(int driverStandingsId, const Race* race, const Driver* driver, int points, int position, int winsNumber);
};

#endif // DRIVER_STANDINGS_HPP