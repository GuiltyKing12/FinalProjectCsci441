#include "Sun.h"

using namespace std;

void Sun::draw() {
    
    glDisable(GL_LIGHTING);
    glPushMatrix();
    {
        GLfloat diffCol[4] = { .65, .8, .9, 1 };
        GLfloat specCol[4] = { 1.0, 1.0, 1.0, 1 };
        GLfloat ambCol[4] = { 1.0, 1.0, 1.0, 1 };
        
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffCol );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specCol );
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 96.0 );
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambCol );
        glTranslatef(position.getX(),
                     position.getY(),
                     position.getZ());
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texHandle);
        glRotatef(currentRevolution, 0, 1, 0);
        gluQuadricTexture(sun,1);
        gluSphere(sun,radius,40,40);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Sun::update() {
    currentRevolution += revolution;
    if(currentRevolution > 360) currentRevolution -= 360;
}

Point Sun::getPosition() {
    return position;
}

double Sun::getRadius() {
    return radius;
}
