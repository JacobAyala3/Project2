#include "simulation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

// Weather Effects
void simulateWeatherEvent(Region& region, int timestep) {
    if (timestep % 10 != 0) return;
    static default_random_engine rng(time(0));
    uniform_int_distribution<int> eventDist(0, 1); // 0 = tornado, 1 = heatwave
    uniform_int_distribution<int> xDist(0, region.getHeight() - 1);
    uniform_int_distribution<int> yDist(0, region.getWidth() - 1);
    int eventType = eventDist(rng);
    int cx = xDist(rng);
    int cy = yDist(rng);
    auto& grid = region.getMutableGrid();
    if (eventType == 0) {
        cout << "\nTornado struck at (" << cx << ", " << cy << ")\n";
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = cx + dx, ny = cy + dy;
                if (nx >= 0 && nx < region.getHeight() && ny >= 0 && ny < region.getWidth()) {
                    grid[nx][ny].population = 0;
                    if (grid[nx][ny].type == 'T' || grid[nx][ny].type == '#')
                        grid[nx][ny].type = '-';
                }
            }
    } else {
        cout << "\nHeatwave is slowing growth temporarily\n";
    }
}
int getWorkers(const Region& region) {
    int total = 0;
    for (const auto& row : region.getGrid())
        for (const auto& c : row)
            if (c.type == 'R') total += c.population;
    return total;
}
int getGoods(const Region& region) {
    int total = 0;
    for (const auto& row : region.getGrid())
        for (const auto& c : row)
            if (c.type == 'I') total += c.population;
    return total;
}
bool simulateGrowth(Region& region, int& workers, int& goods) {
    bool changed = false;
    auto oldGrid = region.getGrid();
    auto& grid = region.getMutableGrid();
    int h = region.getHeight();
    int w = region.getWidth();
    for (int x = 0; x < h; ++x) {
        for (int y = 0; y < w; ++y) {
            char& type = grid[x][y].type;
            int& pop = grid[x][y].population;
            if (type == 'R' && pop < 5) {
                bool hasPower = false;
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int nx = x + dx, ny = y + dy;
                        if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
                            char n = oldGrid[nx][ny].type;
                            if (n == 'T' || n == '#' || n == 'P') {
                                hasPower = true;
                            }
                        }
                    }
                }
                if (hasPower) {
                    pop++;
                    workers++;
                    changed = true;
                }
            }
            if (type == 'I' && pop < 5 && workers > 0) {
                pop++;
                goods++;
                workers--;
                changed = true;
            }
            if (type == 'C' && pop < 5 && workers > 0 && goods > 0) {
                pop++;
                workers--;
                goods--;
                changed = true;
            }
        }
    }

    return changed;
}
void runSimulation(Region& region, int maxSteps, int refreshRate) {
    int workers = getWorkers(region);
    int goods = getGoods(region);
    for (int step = 1; step <= maxSteps; ++step) {
        simulateWeatherEvent(region, step);
        bool changed = simulateGrowth(region, workers, goods);
        cout << "Time Step is : " << step << "\nworkers: " << workers << ", Goods are: " << goods << "\n";
        if (step % refreshRate == 0)
            region.displayRegion();
        if (!changed) {
            cout << "No change detected.\n";
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(refreshRate * 1000));
    }
}
