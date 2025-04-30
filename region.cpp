#include "region.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool Region::loadRegion(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    grid.clear();
    while (getline(file, line)) {
        vector<char> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell.empty() ? '-' : cell[0]);
        }
        grid.push_back(row);
    }

    height = grid.size();
    width = height > 0 ? grid[0].size() : 0;
    return true;
}

void Region::displayRegion() {
    for (const auto& row : grid) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}

void Region::growResidential(bool slowed) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x] == 'R') {
                int growChance = slowed ? 10 : 30; // 10% if slowed, 30% otherwise
                if (rand() % 100 < growChance) {
                    if (x + 1 < width && grid[y][x + 1] == '-') grid[y][x + 1] = 'R';
                }
            }
        }
    }
}

void Region::growCommercial(bool slowed) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x] == 'C') {
                int growChance = slowed ? 5 : 20;
                if (rand() % 100 < growChance) {
                    if (x + 1 < width && grid[y][x + 1] == '-') grid[y][x + 1] = 'C';
                }
            }
        }
    }
}

void Region::growIndustrial(bool slowed) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x] == 'I') {
                int growChance = slowed ? 5 : 20;
                if (rand() % 100 < growChance) {
                    if (x + 1 < width && grid[y][x + 1] == '-') grid[y][x + 1] = 'I';
                }
            }
        }
    }
}

bool Region::noChangeDetected() {
    // Simple placeholder: always simulate full steps
    return false;
}

void Region::setCell(int x, int y, char value) {
    if (y >= 0 && y < height && x >= 0 && x < width) {
        grid[y][x] = value;
    }
}

char Region::getCell(int x, int y) const {
    if (y >= 0 && y < height && x >= 0 && x < width) {
        return grid[y][x];
    }
    return '-';
}
