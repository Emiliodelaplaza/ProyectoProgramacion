#ifndef STRATEGY_RECOMMENDATION_HPP
#define STRATEGY_RECOMMENDATION_HPP

#include <string>

using namespace std;

class StrategyRecommendation {
public:
    string recommendPitStops(const string& weather, int laps, double circuitLength);
    string recommendTireType(const string& weather, int laps);
    string recommendFuelStrategy(int laps, double circuitLength, const string& weather);
    string recommendCarSetup(const string& circuitType, const string& weather);
};

#endif // STRATEGY_RECOMMENDATION_HPP