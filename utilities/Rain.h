#pragma once
#include "ParticleSystem.h"
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

#include <stdlib.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include<ctime>
class Rain : public ParticleSystem {
public:
    Rain() {}
    Rain(Point position, int width, int depth, double minVel, double maxVel, int rate, int maxParticles, std::string type) {
        source = position;
        minVelocity = minVel;
        maxVelocity = maxVel;
        this->maxParticles = maxParticles;
        particlecount = 0;
        this->rate = rate;
        this->width = width;
        this->depth = depth;
        setParticles();
        srand(time(NULL));
        this->type = type;
    }
    ~Rain() {}
    virtual void draw(Point camera, Point pos) override;
    virtual void update() override;
    void setParticles();
protected:
    Vector gravity = Vector(0.0, -9.81, 0.0);
    Point cameraXYZ;
    Point pos;
    int width;
    int depth;
    int maxParticles;
    int particlecount;
};
