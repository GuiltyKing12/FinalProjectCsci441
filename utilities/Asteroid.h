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
#include "Object.h"
#include <string>
#include <iostream>
#include <cmath>

class Asteroid{
	public:
		Asteroid(){}
		Asteroid(double size, double radius ,double angle,  double speed){
			std::cout << "Creating" << std::endl;
			this->size = size;
			this->speed = speed;	
			this->angle = angle;
			this->radius = radius;
			this->position = Point(radius*sin(angle), 0.0, radius*cos(angle));
			string rockFileName = "models/LargeRock.obj";
			obj = new Object(rockFileName.c_str());
		}
		~Asteroid(){}
		void update();
		void draw();
		void setPosition(Point item);
		Point getPosition();
		double getSize();
	protected:
		double radius;
		Point position;
		double angle;
		double speed;
		double size;
		Object *obj;
};
