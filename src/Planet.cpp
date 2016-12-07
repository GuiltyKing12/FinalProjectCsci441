#include "Planet.h"

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
        glutSolidSphere(planetRadius, 30, 30);
    }
    glPopMatrix();
}

void Planet::update() {
    
}
