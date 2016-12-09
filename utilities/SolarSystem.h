#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <ctime>

#include "Planet.h"
#include "Sun.h"
#include "Point.h"
#include "Vector.h"
#include "Ship.h"

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
        srand(time(NULL));
    }
    
    ~SolarSystem() {}
    
    void draw();
    void update(Ship &ship);
    void setSunShader(GLuint handle);
	bool bezierPoints(std::string bezFile, std::vector<Point> &p);
    
protected:
    Sun sun;
    std::vector<Planet> planets;
    void split(const std::string &s, const char* delim, std::vector<std::string> & v);
    void create();
    bool readfile(std::string inputfile);
    bool pause;
    bool gravity;
    GLuint sunshaderhandle;
    GLuint uniformTimeLoc = 0;
    GLuint uniformDistortLoc = 0;
};
