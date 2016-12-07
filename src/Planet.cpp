#include "Planet.h"
#include <iostream>

using namespace std;

void Planet::draw() {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    {
        glTranslatef(position.getX(), position.getY(), position.getZ());
        glRotatef(-45, 1, 0, 0);
        glRotatef(currentRevolution, 0, 0, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texHandle);
        gluQuadricTexture(planet,1);
        gluSphere(planet,planetRadius,20,20);
        glDisable(GL_TEXTURE_2D);
        glTranslatef(planetRadius+100, 0, 0);
        glutSolidSphere(planetRadius/10, 30, 30);
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Planet::update() {
    currentRevolution += revolution;
    if(currentRevolution > 360) currentRevolution = currentRevolution - 360;
}
