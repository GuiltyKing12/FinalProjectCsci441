#pragma once
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
class Skybox {
public:
    Skybox() {
        size = 5000;
        loadSkybox();
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
