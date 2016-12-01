#pragma once

#include "src/Point.h"
#include "src/Vector.h"

class Planet {
public:
    Planet() {}
    
    ~Planet() {}
    
    void draw();
    void update();
protected:
    // Need to draw and move
    Point position;
    Vector direction;
    
    double revolution;
    
    // Extra stuff
    double planetRadius;
    double gravityRadius;
    
    int t; // if we decide to use bezier curve
};
