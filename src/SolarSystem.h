#pragma once

#include <vector>
#include "Planet.h"

class SolarSystem {
public:
    SolarSystem() {}
    
    ~SolarSystem() {}
    
    void draw();
    void update();
    
protected:
    vector<Planet> planets;
    bool pause;
    bool gravity;
};
