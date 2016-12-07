#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Planet.h"
#include "Sun.h"
#include "Point.h"
#include "Vector.h"

class SolarSystem {
public:
    SolarSystem() {}
    SolarSystem(std::string inputfile) {
        if(readfile(inputfile)) {
            fprintf(stdout, "Loaded solarsystem...\n");
        }
        else {
            fprintf(stdout, "Failed to load solarsystem file: %s\n", inputfile.c_str());
        }
    }
    
    ~SolarSystem() {}
    
    void draw();
    void update();
    
protected:
    Sun sun;
    std::vector<Planet> planets;
    void split(const std::string &s, const char* delim, std::vector<std::string> & v);
    void create();
    bool readfile(std::string inputfile);
    bool pause;
    bool gravity;
};
