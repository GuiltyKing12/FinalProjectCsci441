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

#include <vector>
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
		orbitPos = 0;
		currentPoint = 0;
    }
    
    Planet(double radius, Point pos, Vector dir, double revolution, GLuint handle, std::vector<Point> orbitalPath) {
        planetRadius = radius;
        position = pos;
        direction = dir;
        this->revolution = revolution;
        currentRevolution = 0;
        planet = gluNewQuadric();
        texHandle = handle;
        ringPlanet = false;
		orbit = orbitalPath;
		orbitPos = 0;
		currentPoint = 0;
    }
    
    Planet(double radius, Point pos, Vector dir, double revolution, GLuint handle, GLuint handle2, double ringRadius, std::vector<Point> orbitalPath) {
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
		orbit = orbitalPath;
		orbitPos = 0;
		currentPoint = 0;
    }
    
    ~Planet() {}
    
    void draw();
    void update();
    Point getPosition();
    void drawRing( double inner, double outer, unsigned int pts );
    double getRadius();
    bool ringPlanet;
	std::vector<Point> orbit;
	int orbitPos;
	float currentPoint;
	Point evaluateBezierCurve(Point p0, Point p1, Point p2, Point p3, float t);
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
