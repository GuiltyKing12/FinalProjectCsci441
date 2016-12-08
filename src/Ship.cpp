#include "Ship.h"
#include <iostream>
using namespace std;

void Ship::draw() {
    //material
    glPushMatrix();
    {
        glTranslatef(position.getX(),
                     position.getY(),
                     position.getZ());
        glRotatef(heading, 0, 1, 0);
        glRotatef(shipAngle, 0, 0, 1);
        drawBody();
        double currentAngle = wingAngle;
        for(int i = 0; i < 5; i++) {
            glPushMatrix();
            {
                glRotatef(currentAngle, 0, 0, 1);
                glTranslatef(bodySize*2, 0, 0);
                drawWing();
            }
            glPopMatrix();
            currentAngle += 360/5;
        }
    }
    glPopMatrix();
}

void Ship::drawBody() {
    glPushMatrix();
    {
        glScalef(.5, 1, 10);
        glutSolidCube(bodySize);
    }
    glPopMatrix();
    
    glPushMatrix();
    {
        glScalef(1, .5, 10);
        glutSolidCube(bodySize);
    }
    glPopMatrix();
    
    glPushMatrix();
    {
        glTranslatef(bodySize, 0, -bodySize*10/2);
        glPushMatrix();
        {
            glRotatef(thrusterAngle, 1, 0, 0);
            glPushMatrix();
            {
                glScalef(1, .5, 2);
                glutSolidCube(bodySize);
                glRotatef(-thrusterAngle, 1, 0, 0);
                glTranslatef(-bodySize*2, 0, 0);
                glRotatef(thrusterAngle, 1, 0, 0);
                glutSolidCube(bodySize);
            }
            glPopMatrix();
            glTranslatef(0, 0, -bodySize);
            glPushMatrix();
            {
                glDisable(GL_LIGHTING);
                if(forward || backward || left || right) {
                    glRotatef(180, 1, 0, 0);
                    
                    glScalef(1, .5, 2);
                    glutSolidCone(bodySize/2, bodySize, 30, 30);
                    glTranslatef(-bodySize*2, 0, 0);
                    glutSolidCone(bodySize/2, bodySize, 30, 30);
                }
                glEnable(GL_LIGHTING);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void Ship::drawWing() {
    glPushMatrix();
    {
        glRotatef(90, 0, 1, 0);
        glScalef(.2, 1, 1);
        glutSolidCone(bodySize/2, bodySize, 30, 30);
    }
    glPopMatrix();
}

void Ship::animate() {
    wingAngle+=10;
    if(wingAngle == 360) wingAngle = 0;
    
    if(jumped) {
        cooldown--;
        if(cooldown == 0) {
            jumped = false;
            cooldown = 100;
        }
    }
}

void Ship::hyperJump() {
    if(!jumped) {
        position += 10000*direction;
        jumped = true;
    }
}

void Ship::moveForward() {
    position += 20*direction;
    forward = true;
    if(thrusterAngle != 0) thrusterAngle++;
}

void Ship::moveBackward() {
    position -= 20*direction;
    backward = true;
    if(thrusterAngle != -180) thrusterAngle--;
}

void Ship::turnright() {
    if(heading == 360) heading = 0;
    heading++;
    direction = Vector(sin(heading * M_PI / 180),
                       0.0,
                       cos(heading * M_PI / 180));
    right = true;
    if(shipAngle != -45) shipAngle--;
    if(thrusterAngle != 0 && forward) thrusterAngle++;
    else if(thrusterAngle != -180 && backward) thrusterAngle--;
}

void Ship::turnleft() {
    if(heading == 0) heading = 360;
    heading--;
    direction = Vector(sin(heading * M_PI / 180),
                       0.0,
                       cos(heading * M_PI / 180));
    left = true;
    if(shipAngle != 45) shipAngle++;
    if(thrusterAngle != 0 && forward) thrusterAngle++;
    else if(thrusterAngle != -180 && backward) thrusterAngle--;
}

void Ship::rest() {
    backward = false;
    forward = false;
    if(thrusterAngle < -90) thrusterAngle++;
    else if(thrusterAngle > -90) thrusterAngle--;
}

void Ship::notTurn() {
    left = false;
    right = false;
    if(shipAngle < 0) shipAngle++;
    else if(shipAngle > 0) shipAngle--;
}

Point Ship::getPosition() {
    return position;
}

Vector Ship::getDirection() {
    return direction;
}

double Ship::getHeading() {
    return heading;
}

void Ship::setPosition(Point pos) {
    position = pos;
}

void Ship::checkPosition(int bounds) {
    if(position.getX() < -bounds) position.setX(-bounds++);
    else if(position.getX() > bounds) position.setX(bounds--);
    
    if(position.getZ() < -bounds) position.setZ(bounds--);
    else if(position.getZ() > bounds) position.setZ(bounds--);
}
