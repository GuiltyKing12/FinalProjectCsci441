#pragma once
#include "point.h"
#include "vector.h"
#include <iostream>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
class Camera {
  public:
    int mode;
    Point position;
    Point arcPosition;
    Vector camDir;
    
    Point lastLook;
    float camRadius, camTheta, camPhi;
    
  // consturctors for camera
  public:
    Camera() { mode = 3;}
    
    Camera(int setMode, double posX, double posY, double posZ,
                        float cameraRadius, float cameraTheta, float cameraPhi) {
        mode = setMode;
        
        camRadius = cameraRadius;
        camTheta = cameraTheta;
        camPhi = cameraPhi;
        
        switch(mode) {
            case 1 :
                position = Point(posX, posY, posZ);
                break;
            case 2 :
                camDir = Point(posX, posY, posZ) - Point(posX+cameraRadius, posY+cameraRadius, posZ+cameraRadius);
                arcPosition = Point(posX+cameraRadius*camDir.getX(), posY+cameraRadius*camDir.getY(), posZ+cameraRadius*camDir.getZ());
                break;
        }
        recomputeOrientation();
    }
    
  // camera controls
  public:
    void moveForward();
    void moveBackward();
    
    void zoom(float radiusChange);
    void revolve(float theta, float phi);
    
    void switchMode(int setMode);
    
    void recomputeOrientation();
    void look(Point look);
    void fpvLook(Point heroPos, Vector heroDir, float heroHeading);
};
