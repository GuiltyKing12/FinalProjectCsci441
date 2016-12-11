#include "AsteroidSystem.h"
#include <iostream>
/*
 * Other Methods
 */
float getRand() {
	float output = rand() / (float)RAND_MAX;
	return output;
}
/*
 * Class Methods
 */
void AsteroidSystem::update(){
	for(auto& asteroid : asteroids){
		asteroid.update();
	}
}
void AsteroidSystem::draw(){
	for(auto& asteroid : asteroids){
		asteroid.draw();
	}
}
void AsteroidSystem::generateAsteroids(){
	for(int i = 0; i< numAsteroids; i++){
		double size = getRand()*(maxSize-minSize) + minSize;
		double radius = getRand()*(maxRad-minRad) + minRad;
		double angle = getRand()*2*3.14159;
		Asteroid tempAsteroid = Asteroid(size,radius,angle,speed,obj);
		asteroids.push_back(tempAsteroid);
	}
}

std::vector<Asteroid> AsteroidSystem::getAsteroids(){
	return asteroids;
}