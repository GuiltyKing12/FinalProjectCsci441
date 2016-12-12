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

class Moon {
public:
    Moon() {}
    Moon(double theta, double rho, double radius, double planetRadius) {
        this->theta = theta;
        this->rho = rho;
        this->radius = radius;
        this->planetRadius = planetRadius;
    }
    
    ~Moon() {}
    
    void draw();
    void update();

    double theta, rho, radius, planetRadius;
};
