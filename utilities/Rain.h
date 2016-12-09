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
    Rain(Point position, int width, int depth, double minVel, double maxVel, int rate, int maxParticles, std::string type, int minLife, int maxLife, GLuint handle, GLuint shaderHandle) {
        source = position;
        minVelocity = minVel;
        maxVelocity = maxVel;
        this->maxParticles = maxParticles;
        particlecount = 0;
        this->rate = rate;
        this->width = width;
        this->depth = depth;
		this->minLife = minLife;
		this->maxLife = maxLife;
		srand(time(NULL));
        this->type = type;
		this->handle = handle;
		this->shaderHandle = shaderHandle;
		uniformLifeLoc = glGetUniformLocation(shaderHandle, "life");
		uniformMaxLifeLoc = glGetUniformLocation(shaderHandle, "maxLife");
        setParticles();
    }
    ~Rain() {}
    virtual void draw(Point camera, Point pos) override;
    virtual void update() override;
    void setParticles();
protected:
    Vector gravity = Vector(0.0, 0.0, -9.81);
    Point cameraXYZ;
    Point pos;
    int width;
    int depth;
	int minLife;
	int maxLife;
    int maxParticles;
    int particlecount;
	GLuint handle = 0;
	GLuint shaderHandle = 0;
	GLuint uniformLifeLoc = 0;
	GLuint uniformMaxLifeLoc = 0;
};
