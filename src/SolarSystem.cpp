#include "SolarSystem.h"

using namespace std;

void SolarSystem::draw() {
    for(int i = 0; i < planets.size(); i++) {
        planets[i].draw();
    }
}

void SolarSystem::update() {
    
}
