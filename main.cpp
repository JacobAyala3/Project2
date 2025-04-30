#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "region.h"
#include "simulation.h"

using namespace std;

string getValueAfterColon(const string& line) {
    size_t pos = line.find(':');
    if (pos != string::npos)
        return line.substr(pos + 1);
    return "";
}

int main() {
    string configFile;
    cout << "Enter config filename: ";
    cin >> configFile;

    ifstream file(configFile);
    if (!file) {
        cerr << "Error loading the config file." << endl;
        return 1;
    }

    string regionLine, stepsLine, rateLine;
    getline(file >> ws, regionLine);
    getline(file >> ws, stepsLine);
    getline(file >> ws, rateLine);

    // Trim and parse
    string regionFile = getValueAfterColon(regionLine);
    string stepsStr = getValueAfterColon(stepsLine);
    string rateStr = getValueAfterColon(rateLine);

    regionFile.erase(remove_if(regionFile.begin(), regionFile.end(), ::isspace), regionFile.end());
    stepsStr.erase(remove_if(stepsStr.begin(), stepsStr.end(), ::isspace), stepsStr.end());
    rateStr.erase(remove_if(rateStr.begin(), rateStr.end(), ::isspace), rateStr.end());

    // Debug
    cout << "regionFile: [" << regionFile << "]\n";
    cout << "steps: [" << stepsStr << "]\n";
    cout << "rate: [" << rateStr << "]\n";

    int maxTimeSteps = stoi(stepsStr);
    int refreshRate = stoi(rateStr);

    Region region;
    if (!region.loadRegion(regionFile)) {
        cerr << "Error loading the region file." << endl;
        return 1;
    }

    cout << "\nInitial region state this is time step 0:\n";
    region.displayRegion();
    runSimulation(region, maxTimeSteps, refreshRate);

    return 0;
}
