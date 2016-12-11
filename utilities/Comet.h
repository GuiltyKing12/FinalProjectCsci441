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
#include "Ship.h"
#include "Vector.h"
#include "Object.h"
#include <string>
#include <iostream>
#include <cmath>

class Comet{
	public:
		Comet(){}
		Comet(double size, Point position, double speed){
			this->size = size;
			this->position = position;
			this->speed = speed;	
			string rockFileName = "models/SmallRock.obj";
			obj = new Object(rockFileName.c_str());
		}
		void update();
		void draw();
		void setPosition(Point item);
		Point getPosition();
		double getSize();
		void didHitShip(Ship& ship);
	protected:
		Point position;
		double angle;
		double speed;
		double size;
		Object *obj;
};
