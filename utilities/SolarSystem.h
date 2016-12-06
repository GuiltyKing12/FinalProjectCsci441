#pragma once

#include <vector>
#include "Planet.h"
#include "Point.h"
#include "Vector.h"

class SolarSystem {
public:
    SolarSystem() {}
    
    ~SolarSystem() {}
    
    void draw();
    void update();
    
protected:
    std::vector<Planet> planets;
    bool pause;
    bool gravity;
};
