#pragma once

// Very important!!!
// GLEW MUST BE INCLUDED BEFORE gl.h is included
#include <GL/glew.h>		// OpenGL Extension Wrangler

// Include our OpenGL & GLUT libraries
// GLUT automatically includes glu.h and gl.h
#ifdef __APPLE__
#include <GLUT/glut.h>	// GLUT, GLU, GL Libraries for Mac
#include <SOIL.h>  	// Simple OpenGL Image Library
#else
#include <GL/glut.h>	// GLUT, GLU, GL Libraries for Windows or *nix
#include <SOIL/SOIL.h>  	// Simple OpenGL Image Library
#endif

#include <stdlib.h>
#include <ctime>
#include <vector>

#include "Moon.h"

class MoonSystem {
public:
    MoonSystem() {}
    MoonSystem(double radius, int numMoons, double moonRad) {
        this->radius = radius;
        this->numMoons = numMoons;
        this->moonRad = moonRad;
        setup();
    }
    
    ~MoonSystem() {}
    void setup();
    void draw();
    void update();
protected:
    double radius, moonRad;
    int numMoons;
    std::vector<Moon> moons;
};
