#include "DriverStandings.hpp"

DriverStandings::DriverStandings()
    : driverStandingsId(0), race(nullptr), driver(nullptr), points(0), position(0), winsNumber(0) {}

DriverStandings::DriverStandings(int driverStandingsId, const Race* race, const Driver* driver, int points, int position, int winsNumber)
    : driverStandingsId(driverStandingsId), race(race), driver(driver), points(points), position(position), winsNumber(winsNumber) {}