#include "StrategyRecommendation.hpp"

using namespace std;

string StrategyRecommendation::recommendPitStops(const string& weather, int laps, double circuitLength) {
    // Ejemplo de lógica: Asumir más paradas en condiciones de lluvia
    if (weather == "rainy") {
        return to_string(laps / 20 + 1) + " pit stops are recommended due to wet conditions.";
    } else {
        return to_string(laps / 30 + 1) + " pit stops are recommended.";
    }
}

string StrategyRecommendation::recommendTireType(const string& weather, int laps) {
    // Decidir sobre el tipo de neumático según el clima
    if (weather == "rainy") {
        return "Wet tires are recommended.";
    } else if (weather == "hot") {
        return "Soft tires are recommended for better grip.";
    } else {
        return "Hard tires are recommended for durability.";
    }
}

string StrategyRecommendation::recommendFuelStrategy(int laps, double circuitLength, const string& weather) {
    double fuelPerLap = 2.4; // Consumo estimado de combustible por vuelta en kg
    double fuelNeeded = laps * fuelPerLap;
    return "Estimated fuel needed: " + to_string(fuelNeeded) + " kg.";
}

string StrategyRecommendation::recommendCarSetup(const string& circuitType, const string& weather) {
    if (circuitType == "highDownforce" && weather == "rainy") {
        return "Increase downforce and use full wets.";
    } else if (circuitType == "highSpeed") {
        return "Decrease downforce for better top speed.";
    } else {
        return "Standard setup recommended.";
    }
}