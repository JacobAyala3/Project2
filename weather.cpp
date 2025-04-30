#include "weather.h"
#include <cstdlib>
#include <ctime>

using namespace std;

WeatherEvent getRandomWeather(int timeStep) {
    if (timeStep % 5 != 0) return WeatherEvent::NONE;

    int roll = rand() % 10;
    if (roll < 2) return WeatherEvent::TORNADO;   // 20% chance
    if (roll < 5) return WeatherEvent::HEATWAVE;  // 30% chance
    return WeatherEvent::NONE;
}

string weatherToString(WeatherEvent event) {
    switch (event) {
        case WeatherEvent::TORNADO: return "Tornado";
        case WeatherEvent::HEATWAVE: return "Heatwave";
        default: return "No Event";
    }
}
