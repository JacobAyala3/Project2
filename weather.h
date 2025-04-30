#ifndef WEATHER_H
#define WEATHER_H

#include <string>
using namespace std;

enum class WeatherEvent {
    NONE,
    TORNADO,
    HEATWAVE
};

WeatherEvent getRandomWeather(int timeStep);
string weatherToString(WeatherEvent event);

#endif
