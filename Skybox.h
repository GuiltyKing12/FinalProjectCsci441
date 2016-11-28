#pragma once

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

class Skybox {
public:
    Skybox() {
        loadSkybox();
        size = 5000;
    }
    
    Skybox(int size) {
        this->size = size;
        loadSkybox();
    }
    
    void draw();
    
private:
    GLuint frontSide;
    GLuint backSide;
    GLuint leftSide;
    GLuint rightSide;
    GLuint topSide;
    GLuint bottomSide;
    
    int size;
    
    void loadSkybox();
    
};
