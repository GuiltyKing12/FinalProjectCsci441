#pragma once

#include "Point.h"
#include "Vector.h"

class Sun {
public:
    Sun() {}
    ~Sun() {}
    
    void draw();
    void update();
protected:
    Point position;
    
    double radius;
    double gravityRadius;
    
    double revolution;
    
    /*
     we might want to make this have a light source attached
     in this or main eiter way should work
    */
};
