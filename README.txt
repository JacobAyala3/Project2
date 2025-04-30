Build Instructions:
-------------------
To compile the program, run the following command:
g++ main.cpp simulation.cpp region.cpp weather.cpp -o simcity
To run the program after compiling:
./simcity
Make sure the following files are in the same directory as the executable:
- config1.txt (contains the region file name, number of steps, refresh rate)
- region1.csv (the map of the city in CSV format)

Bonus Feature:
- A weather system that randomly introduces Tornadoes and Heatwaves.
- Tornadoes destroy a random zone.
- Heatwaves slow down growth and alert the user with a message.