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

#include "Point.h"
#include "Vector.h"

class Sun {
public:
    Sun() {}
    Sun(double radius, Point position, double revolution) {
        this->radius = radius;
        this->position = position;
        this->revolution = revolution;
    }
    ~Sun() {}
    
    void draw();
    void update();
protected:
    Point position;
    
    double radius;
    double gravityRadius;
    
    double revolution;
    
    /*
     we might want to make this have a light source attached
     in this or main eiter way should work
    */
};
