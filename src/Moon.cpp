#include "Moon.h"
#include <iostream>
#include <math.h>

using namespace std;

void Moon::draw() {
    glPushMatrix();
    {
        glutSolidSphere(planetRadius, 30, 30);
    }
    glPopMatrix();
}

void Moon::update() {
    theta++;
    if(theta == 360) theta = 0;
}
