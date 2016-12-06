#include "Planet.h"
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
void Planet::draw() {
    glPushMatrix();
    {
        glTranslatef(position.getX(), position.getY(), position.getZ());
        glutSolidSphere(planetRadius, 30, 30);
    }
    glPopMatrix();
}

void Planet::update() {
    
}
