#include "Sun.h"

using namespace std;

void Sun::draw() {
    glPushMatrix();
    {
        glTranslatef(position.getX(),
                     position.getY(),
                     position.getZ());
        
        glutSolidSphere(radius, 30, 30);
    }
    glPopMatrix();
}

void Sun::update() {
    
}
