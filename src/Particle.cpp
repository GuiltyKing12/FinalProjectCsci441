#include "Particle.h"

void Particle::draw() {
    GLfloat diffCol[4] = { 1.0, 1.0, 1.0, 1 };
    GLfloat specCol[4] = { 1.0, 1.0, 1.0, 1 };
    GLfloat ambCol[4] = { 0.8, 0.8, 0.8, 1 };
    
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffCol );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specCol );
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 96.0 );
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambCol );
    
    glBegin(GL_QUADS); {
        glNormal3f( 0, 0, 1 );
        glTexCoord2f( 0, 0.01 );
        glVertex3f(-20, 20, 0);
        
        glNormal3f( 0, 0, 1 );
        glTexCoord2f( 0, 1 );
        glVertex3f(-20, 0, 0);
        
        glNormal3f( 0, 0, 1 );
        glTexCoord2f( 1, 1 );
        glVertex3f(20, 0, 0);
        
        glNormal3f( 0, 0, 1 );
        glTexCoord2f( 1, 0.01 );
        glVertex3f(20, 20, 0);
    } glEnd();
}

void Particle::update(Point update) {
    position = update;
    if(currentLife != 0) currentLife--;
}

Point Particle::getPoint() {
    return position;
}

Vector Particle::getHeading() {
    return heading;
}

double Particle::getVelocity() {
    return velocity;
}

double Particle::getCurrentLife() {
    return currentLife;
}

double Particle::getMaxLife() {
	return life;
}

void Particle::setPoint(Point update) {
    position = update;
}

void Particle::setHeading(Vector heading) {
    this->heading = heading;
}
