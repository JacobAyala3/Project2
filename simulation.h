#ifndef SIMULATION_H
#define SIMULATION_H
#include "region.h"
void runSimulation(Region& region, int maxSteps, int refreshRate);
void simulateWeatherEvent(Region& region, int timestep);
int getWorkers(const Region& region);
int getGoods(const Region& region);
bool simulateGrowth(Region& region, int& workers, int& goods);
#endif
