#include "Planet.h"
#include <iostream>

using namespace std;

void Planet::draw() {
    glPushMatrix();
    {
        GLfloat diffCol[4] = { .65, .8, .9, 1 };
        GLfloat specCol[4] = { 1.0, 1.0, 1.0, 1 };
        GLfloat ambCol[4] = { 0.8, 0.8, 0.8, 1 };
        
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffCol );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specCol );
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 96.0 );
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambCol );
        glTranslatef(position.getX(), position.getY(), position.getZ());
        glRotatef(currentRevolution, 0, 1, 0);
        glutSolidSphere(planetRadius, 30, 30);
        glTranslatef(planetRadius+100, 0, 0);
        glutSolidSphere(planetRadius/10, 30, 30);
    }
    glPopMatrix();
}

void Planet::update() {
    currentRevolution += revolution;
    if(currentRevolution > 360) currentRevolution = currentRevolution - 360;
}
