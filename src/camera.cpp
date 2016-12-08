#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "camera.h"
#include <math.h>

/** MODE 1 - Free cam control **/
void Camera::moveForward() {
    if(mode == 1) {
        position = position + 50*camDir;
        recomputeOrientation();
    }
}

void Camera::moveBackward() {
    if(mode == 1) {
        position = position + -50*camDir;
        recomputeOrientation();
    }
}

/** MODE 2 - ARCball controls **/
void Camera::zoom(float radiusChange) {
    if(mode == 2) camRadius += radiusChange;
}

/** General movement control for both Modes **/
void Camera::revolve(float theta, float phi) {
    
        camTheta += theta;
    
        camPhi += phi;
        if(camPhi > 3.14) camPhi -= phi;
        else if(camPhi < 0) camPhi -= phi;
    
        recomputeOrientation();
}

void Camera::switchMode(int setMode) {
    mode = setMode;
    if(setMode == 1) {
        position =  Point(-camDir.getX() * sinf(camTheta) * sin(camPhi) + camRadius, -camDir.getY() * -cosf(camPhi) + camRadius, -camDir.getZ() * -cosf(camTheta) * sinf(camPhi) + camRadius);
        camPhi = M_PI / 3.0f;
        camTheta = -1.0f;
    }
    else if(setMode == 2) {
        camTheta = M_PI / 3.0f;
        camPhi = 2.8f;
    }
    recomputeOrientation();
}

/** Functions to control the orientation and where to look **/

void Camera::recomputeOrientation() {
    camDir.setX(sinf(camTheta) * sin(camPhi));
    camDir.setY(-cosf(camPhi));
    camDir.setZ(-cosf(camTheta) * sinf(camPhi));
    
    camDir.normalize();
}

void Camera::look(Point look) {
    switch(mode) {
        case 1 :
            gluLookAt(position.getX(), position.getY(), position.getZ(),
                      camDir.getX()+position.getX(), camDir.getY()+position.getY(), camDir.getZ()+position.getZ(),
                      0, 1, 0);
            break;
        case 2 :
            Vector currentDir = camDir * camRadius;
            lastLook = look;
            arcPosition = Point(currentDir.getX()+look.getX(), currentDir.getY()+look.getY(), currentDir.getZ()+look.getZ());
            gluLookAt(arcPosition.getX(), arcPosition.getY(), arcPosition.getZ(),
                      look.getX(), look.getY(), look.getZ(),
                      0, 1, 0);
            break;
    }
}

void Camera::fpvLook(Point heroPos, Vector heroDir, float heroHeading) {
    /*Vector ortho = cross(heroDir, Vector(1, 0, 0));
    Vector u_n = heroDir / heroDir.mag();
    float c = cos(heroHeading);
    float s = sin(heroHeading);
    Vector pt(
      (c + u_n.getX() * u_n.getX() * (1 - c)) * ortho.getX()
        + (u_n.getX() * u_n.getY() * (1 - c) - u_n.getZ() * s) * ortho.getY()
        + (u_n.getX() * u_n.getZ() * (1 - c) + u_n.getY() * s) * ortho.getZ(),

      (u_n.getY() * u_n.getX() * (1 - c) + u_n.getZ() * s) * ortho.getX()
        + (c + u_n.getY() * u_n.getY() * (1 - c)) * ortho.getY()
        + (u_n.getY() * u_n.getZ() * (1 - c) - u_n.getX() * s) * ortho.getZ(),

      (u_n.getZ() * u_n.getX() * (1 - c) - u_n.getY() * s) * ortho.getX()
        + (u_n.getZ() * u_n.getY() * (1 - c) + u_n.getX() * s) * ortho.getY()
        + (c + u_n.getZ() * u_n.getZ() * (1 - c)) * ortho.getZ()
    );

    u_n = u_n * 15;
    pt = pt * 10;

    gluLookAt(heroPos.getX() + u_n.getX(), heroPos.getY() + u_n.getY(), heroPos.getZ() + u_n.getZ(),
              heroPos.getX() - pt.getX(), heroPos.getY() - pt.getY() + 20, heroPos.getZ() - pt.getZ(),
              0, 1, 0);*/
    Point look = heroPos +  -1*heroDir;
    gluLookAt(look.getX(), look.getY(), look.getZ(),
              heroPos.getX(), heroPos.getY(), heroPos.getZ(),
              0, 1, 0);
}
