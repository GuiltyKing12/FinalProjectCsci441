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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <math.h>

#include "Point.h"
#include "Vector.h"

class Ship {
public:
    Ship() {}
    Ship(Point pos, double size) {
        position = pos;
        bodySize = size;
        wingAngle = 0;
        shipAngle = 0;
        thrusterAngle = -90;
        direction = Vector(0, 0, 1);
        cooldown = 100;
        jumped = false;
        left = false;
        right = false;
        forward = false;
        backward = false;
    }
    void draw();
    void drawBody();
    void drawWing();
    void animate();
    void hyperJump();
    void moveForward();
    void moveBackward();
    void turnright();
    void turnleft();
    void rest();
    void notTurn();
    Point getPosition();
    Vector getDirection();
    double getHeading();
    void setPosition(Point pos);
    void checkPosition(int size);
    
protected:
    Point position;
    Vector direction;
    double heading;
    double bodySize;
    double wingAngle;
    double thrusterAngle;
    double shipAngle;
    int cooldown;
    bool jumped;
    bool left;
    bool right;
    bool forward;
    bool backward;
};
