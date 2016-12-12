#include "MoonSystem.h"
#include <math.h>
void MoonSystem::setup() {
    for(int i = 0; i < numMoons; i++) {
        double theta = rand()%(361);
        double rho = rand()%(181);
        moons.push_back(Moon(theta, rho, moonRad, 5));
    }
}

void MoonSystem::draw() {
    glPushMatrix();
    for(int i = 0; i < moons.size(); i++) {
        glTranslatef(radius*cos(moons[i].theta)*sin(moons[i].rho),
                     radius*cos(moons[i].theta)*cos(moons[i].rho),
                     radius*sin(moons[i].rho));
        moons[i].draw();
    }
    glPopMatrix();
}

void MoonSystem::update() {
    for(int i = 0; i < moons.size(); i++) {
        moons[i].update();
    }
}
