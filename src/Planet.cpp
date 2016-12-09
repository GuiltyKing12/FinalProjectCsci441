#include "Planet.h"

#include <math.h>
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
        glPushMatrix();
        {
            if(ringPlanet) {
                drawRing(ringRadius, ringRadius+100, 100);
            }
        }
        glPopMatrix();
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

    position = evaluateBezierCurve(orbit[orbitPos], orbit[orbitPos + 1], orbit[orbitPos + 2], orbit[orbitPos + 3], currentPoint);
    if(currentPoint > 1) {
        orbitPos += 3;
        currentPoint = 0;
    }
    if(orbitPos == orbit.size() - 1) orbitPos = 0;
}

void Planet::drawRing( double inner, double outer, unsigned int pts )
{
    glBegin( GL_QUAD_STRIP );
    for( unsigned int i = 0; i <= pts; ++i )
    {
        float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
        glVertex2f( inner * cos( angle ), inner * sin( angle ) );
        glVertex2f( outer * cos( angle ), outer * sin( angle ) );
    }
    glEnd();
}

// Computes a point along a Bezier curve
Point Planet::evaluateBezierCurve( Point p0, Point p1, Point p2, Point p3, float t ) {
    Point ptA = ((-1.0f * p0) + (3.0f * p1) + (-3.0f * p2) + p3) * pow(t, 3);
    Point ptB = ((3.0f * p0) + (-6.0f * p1) + (3.0f * p2)) * pow(t, 2);
    Point ptC = ((-3.0f * p0) + (3.0f * p1)) * t;
    
    Point curvePoint = p0 + ptA + ptB + ptC;
    return curvePoint;
}
