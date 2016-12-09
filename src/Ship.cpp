#include "Ship.h"

using namespace std;

void Ship::draw() {
    //material
    glPushMatrix();
    {
		GLfloat diffCol[4] = { .65, .8, .9, 1 };
        GLfloat specCol[4] = { 1.0, 1.0, 1.0, 1 };
        GLfloat ambCol[4] = { 1.0, 1.0, 1.0, 1 };
        
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffCol );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specCol );
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 96.0 );
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambCol );
		
        glTranslatef(position.getX(),
                     position.getY(),
                     position.getZ());
        if(exploded) explode();
        else {
            if(sun) {
                glUseProgram(shipshaderhandle1);
                glUniform1f(uniformRatioLoc, sunDist);
            }
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
            if(sun) glUseProgram(0);
            glPopMatrix();
            glTranslatef(0, 0, -bodySize);
            glPushMatrix();
            {
                glDisable(GL_LIGHTING);
                if(forward || backward || left || right) {
					glPushMatrix();
                    glRotatef(180, 1, 0, 0);
                   
					glScalef(1, .5, 2);
					glutSolidCone(bodySize/2, bodySize, 30, 30);
					glTranslatef(-bodySize*2, 0, 0);
					glutSolidCone(bodySize/2, bodySize, 30, 30);
					glPopMatrix();
					glPushMatrix();
						doSort();
						if(thrusterAngle == 0 || thrusterAngle == -180 && forward) {
							glScalef(bodySize/10, bodySize/10, bodySize/10);
							thrusterEffects.draw(cameraPos, pos);
							thrusterEffects.update();
							glUseProgram(0);
						}
					glPopMatrix();
				
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

void Ship::update(Point camPos, Point pos) {
    cameraPos = camPos;
    this->pos = pos;
}

void Ship::explode() {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    {
        Vector view = (pos - cameraPos);
        
        //view.setY(0);
        view.normalize();
        Vector rainDir = Vector(0.0, 0.0, 1.0);
        
        double angle = acos(dot(rainDir, view) / (rainDir.mag() * view.mag())) * 180 / M_PI;
        Vector axis = cross(rainDir, view);
        axis.normalize();
        glRotatef(angle, axis.getX(), axis.getY(), axis.getZ());
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, explosionTexHandle);
        glBegin(GL_QUADS); {
            glNormal3f( 0, 0, 1 );
            glTexCoord2f( 0, 0.01 );
            glVertex3f(-bodySize*10, bodySize*10, 0);
            
            glNormal3f( 0, 0, 1 );
            glTexCoord2f( 0, 1 );
            glVertex3f(-bodySize*10, -bodySize*10, 0);
            
            glNormal3f( 0, 0, 1 );
            glTexCoord2f( 1, 1 );
            glVertex3f(bodySize*10, -bodySize*10, 0);
            
            glNormal3f( 0, 0, 1 );
            glTexCoord2f( 1, 0.01 );
            glVertex3f(bodySize*10, bodySize*10, 0);
        } glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
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

void Ship::nearSun(bool isNear, double ratio) {
    sun = isNear;
    sunDist = ratio;
}

void Ship::setShipShader1(GLuint handle) {
    shipshaderhandle1 = handle;
    uniformRatioLoc = glGetUniformLocation(shipshaderhandle1, "ratio");
}

void Ship::setThrusterShader(GLuint handle, GLuint shaderHandle) {
	Point thruster(0.0, 0.0, -bodySize*5-bodySize);
	
	thrusterEffects = Rain(thruster, bodySize*100, 1, .002, .05, 5, 35, "R", 10, 100, handle, shaderHandle);
}

void Ship::setExpTex(GLuint handle) {
    explosionTexHandle = handle;
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

bool Ship::sortByDot(Particle &lhs, Particle &rhs) {
	Vector viewPath = pos - cameraPos;
	viewPath.normalize();
	Vector lh = cameraPos - lhs.getPoint();
	Vector rh = cameraPos - rhs.getPoint();
	
	if(direction.getZ() > 0) {
		return dot(lh, viewPath) < dot(rh, viewPath);
	}
	else return dot(lh, viewPath) > dot(rh, viewPath);
}
