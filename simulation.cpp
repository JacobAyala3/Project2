#include "simulation.h"
#include "weather.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void runSimulation(Region& region, int maxTimeSteps, int refreshRate) {
    srand(time(0));
    bool slowedGrowth = false;

    for (int currentTimeStep = 1; currentTimeStep <= maxTimeSteps; ++currentTimeStep) {
        cout << "\nTime Step: " << currentTimeStep << endl;

        // Weather event
        WeatherEvent event = getRandomWeather(currentTimeStep);
        cout << "Weather event this step: " << weatherToString(event) << endl;

        if (event == WeatherEvent::TORNADO) {
            int x = rand() % region.getWidth();
            int y = rand() % region.getHeight();
            cout << "Tornado hit (" << x << "," << y << ") and destroyed the zone!" << endl;
            region.setCell(x, y, '-');
        }
        else if (event == WeatherEvent::HEATWAVE) {
            cout << "Heatwave active! Growth is slowed this step." << endl;
            slowedGrowth = true;
        } else {
            slowedGrowth = false;
        }

        region.growResidential(slowedGrowth);
        region.growCommercial(slowedGrowth);
        region.growIndustrial(slowedGrowth);

        if (currentTimeStep % refreshRate == 0) {
            region.displayRegion();
        }

        if (region.noChangeDetected()) {
            cout << "No change detected. Halting simulation." << endl;
            break;
        }
    }

    cout << "\nFinal region state after simulation:" << endl;
    region.displayRegion();
}
