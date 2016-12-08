#include "Planet.h"
#include <iostream>

using namespace std;

void Planet::draw() {
    glPushMatrix();
    {
        GLfloat diffCol[4] = { .65, .8, .9, 1 };
        GLfloat specCol[4] = { 1.0, 1.0, 1.0, 1 };
        GLfloat ambCol[4] = { 1.0, 1.0, 1.0, 1 };
        
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffCol );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specCol );
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 96.0 );
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambCol );
        
        glTranslatef(position.getX(), position.getY(), position.getZ());
        glRotatef(-45, 1, 0, 0);
        glRotatef(currentRevolution, 0, 0, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texHandle);
        gluQuadricTexture(planet,1);
        gluSphere(planet,planetRadius,40,40);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        glTranslatef(planetRadius+100, 0, 0);
        glutSolidSphere(planetRadius/10, 30, 30);
    }
    glPopMatrix();
    
}

Point Planet::getPosition() {
    return position;
}

double Planet::getRadius() {
    return planetRadius;
}

void Planet::update() {
    currentRevolution += revolution;
    if(currentRevolution > 360) currentRevolution = currentRevolution - 360;
}
