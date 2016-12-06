#pragma once

#include "Point.h"
#include "Vector.h"

class Planet {
public:
    Planet() {
        position = Point(0.0, 0.0, 0.0);
        direction = Vector(0.0, 1.0, 0.0);
        revolution = 10;
        planetRadius = 10;
        gravityRadius = 20;
    }
    
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
