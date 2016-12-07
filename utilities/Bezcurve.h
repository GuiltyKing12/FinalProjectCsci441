#pragma once

class Bezcurve {
public:
    Bezcurve() {}
    
    Bezcurve(std::string inputfile) {
        
    }
    
    void draw();
    Point getPosition();
    
protected:
    std::vector<Point> bezpoints;
};
