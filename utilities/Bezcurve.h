#pragma once

#include <vector>
#include <string>
#include "Point.h"

class Bezcurve {
public:
    Bezcurve() {}
    
    Bezcurve(std::string inputfile) {
        
    }
    
    void draw();
    Point getPosition(double t);
    
protected:
    std::vector<Point> bezpoints;
};
