#pragma once
#include "Particle.h"
#include <vector>
#include "Point.h"
#include "Camera.h"
#include "Hero.h"

class ParticleSystem {
public:
    virtual void draw(Point camera, Point pos) = 0;
    virtual void update() = 0;
    virtual ~ParticleSystem() {};
    int numParticles() {return particles.size();}
    std::vector<Particle*> getParticles() {return particles;}
    std::vector<Particle*> particles;
    std::string type;
protected:
    Point source;
    double minVelocity;
    double maxVelocity;
    int rate;
};
