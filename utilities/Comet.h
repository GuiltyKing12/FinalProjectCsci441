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

class Comet{
				public:
								Comet(){}
								Comet(double size, Point position, Vector direction){
												this->size = size;
												this->position = position;
												this->direction = direction;	

								}
								void update();
								void draw();
								Point getPosition();
								double getSize();
				protected:
								Point position;
								Vector direction;
								double size;
}
