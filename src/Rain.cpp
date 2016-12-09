#include "Rain.h"
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

void Rain::draw(Point camera, Point pos) {
    // take the camera position and direction to figure out how to rotate
    cameraXYZ = camera;
    this->pos = pos;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, handle);
    for(int i = 0; i < particles.size(); i++) {
        glPushMatrix(); {
            Vector view = (this->pos - cameraXYZ);
            
            //view.setY(0);
            view.normalize();
            Vector rainDir = Vector(0.0, 0.0, 1.0);
            
            Point position = particles[i].getPoint();
            glTranslatef(position.getX(), position.getY(), position.getZ());
            double angle = acos(dot(rainDir, view) / (rainDir.mag() * view.mag())) * 180 / M_PI;
            Vector axis = cross(rainDir, view);
            axis.normalize();
            glRotatef(angle, axis.getX(), axis.getY(), axis.getZ());
            
            particles[i].draw();
        } glPopMatrix();
    }
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Rain::update() {
    //update current particle positions
    for(int i = 0; i < particles.size(); i++) {
        Vector heading = particles[i].getHeading();
        Point update = particles[i].getPoint() + heading * particles[i].getVelocity();
        particles[i].update(update);
        particles[i].setHeading(heading + gravity);
        if(particles[i].getCurrentLife() == 0) {
            particles.erase(particles.begin()+(i));
            particlecount--;
        }
    }
    //add more particles to system
    setParticles();
}

void Rain::setParticles() {
    if(particlecount < maxParticles) {
        for(int i = 0; i < rate; i++) {
            Point spawn(source.getX()+rand()%(width/2 + 1) - rand()%(width/2 + 1),
                        source.getY()+rand()%(depth/2 + 1) - rand()%(depth/2 + 1),
                        source.getZ()+rand()%(width/2 + 1) - rand()%(width/2 + 1));
            float velocity = (minVelocity*100 + (rand()%(int)(maxVelocity*100 - minVelocity*100 +1))) / 100;
			
			int life = minLife + (rand()%(maxLife - minLife + 1));
			
            particles.push_back(Particle(spawn, velocity, 1, life, Vector(0,0,-1)));
            particlecount++;
        }
    }
}
