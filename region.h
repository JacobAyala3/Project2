#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>
using namespace std;

class Region {
private:
    vector<vector<char>> grid;
    int height;
    int width;

public:
    bool loadRegion(const string& filename);
    void displayRegion();
    void growResidential(bool slowed = false);
    void growCommercial(bool slowed = false);
    void growIndustrial(bool slowed = false);
    bool noChangeDetected();

    int getHeight() const { return height; }
    int getWidth() const { return width; }
    void setCell(int x, int y, char value);
    char getCell(int x, int y) const;

    int calculateTotalPollution() const;
    int calculatePollutionInArea(int x1, int y1, int x2, int y2) const;
};

#endif
