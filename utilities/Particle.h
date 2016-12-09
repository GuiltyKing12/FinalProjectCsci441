#pragma once
#include "Point.h"
#include "Vector.h"
#include <GL/glew.h>		// OpenGL Extension Wrangler

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <SOIL/SOIL.h>  	// Simple OpenGL Image Library
class Particle {
public:
    Particle() {}
    Particle(Point source, double velocity, double mass, Vector heading) {
        position = source;
        this->velocity = velocity;
        this->heading = heading;
        this->mass = mass;
        life = 0;
    }
    Particle(Point source, double velocity, double mass, double life, Vector heading) {
        position = source;
        this->velocity = velocity;
        this->heading = heading;
        this->mass = mass;
        this->life = life;
        currentLife = this->life;
    }
    void draw();
    void update(Point update);
    Point getPoint();
    double getVelocity();
    Vector getHeading();
    double getCurrentLife();
	double getMaxLife();
    void setPoint(Point update);
    void setHeading(Vector heading);
private:
    Point position;
    Vector heading;
    double velocity;
    double life;
    double mass;
    double currentLife;
    GLuint particleTexHandle;
};
