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
#include "Object.h"
#include "Asteroid.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
class AsteroidSystem{
public:
	AsteroidSystem(){}
	AsteroidSystem(double minRad, double maxRad, double minSize, double maxSize, int numAsteroids, double speed	){
		this->minRad = minRad;
		this->maxRad = maxRad;
		this->minSize = minSize;
		this->maxSize = maxSize;
		this->numAsteroids = numAsteroids;
		this->speed = speed;
		string rockFileName = "models/LargeRock.obj";
		cout << rockFileName << endl;
		obj = new Object(rockFileName.c_str());
	}
	~AsteroidSystem(){}
	void update();
	void draw();
	void generateAsteroids();
protected:
	Object* obj;
	vector<Asteroid> asteroids;
	double minRad;
	double maxRad;
	double minSize;
	double maxSize;
	int numAsteroids;
	double speed;
};