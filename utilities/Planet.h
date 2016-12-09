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

class Planet {
public:
    Planet() {
        position = Point(0.0, 0.0, 0.0);
        direction = Vector(0.0, 1.0, 0.0);
        revolution = 10;
        currentRevolution = 0;
        planetRadius = 10;
        gravityRadius = 20;
    }
    
    Planet(double radius, Point pos, Vector dir, double revolution, GLuint handle) {
        planetRadius = radius;
        position = pos;
        direction = dir;
        this->revolution = revolution;
        currentRevolution = 0;
        planet = gluNewQuadric();
        texHandle = handle;
        ringPlanet = false;
    }
    
    Planet(double radius, Point pos, Vector dir, double revolution, GLuint handle, GLuint handle2, double ringRadius) {
        planetRadius = radius;
        position = pos;
        direction = dir;
        this->revolution = revolution;
        currentRevolution = 0;
        planet = gluNewQuadric();
        texHandle = handle;
        ringHandle = handle2;
        this->ringRadius = ringRadius;
        ringPlanet = true;
    }
    
    ~Planet() {}
    
    void draw();
    void update();
    Point getPosition();
    void drawRing( double inner, double outer, unsigned int pts );
    double getRadius();
    bool ringPlanet;
protected:
    // Need to draw and move
    Point position;
    Vector direction;
    
    GLUquadric* planet;
    GLuint texHandle;
    GLuint ringHandle;
    double revolution;
    double currentRevolution;
    
    // Extra stuff
    double planetRadius;
    double ringRadius;
    double gravityRadius;
    
    int t; // if we decide to use bezier curve
};
