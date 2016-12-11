#include "Asteroid.h"
#include <iostream>
void Asteroid::update(){
	angle += speed*0.005;
	position.setX(radius*sin(angle));
	position.setZ(radius*cos(angle));
}
void Asteroid::draw(){
	glPushMatrix();
	{
		GLfloat diffCol[4] = { 1.0, 1.0, 1.0, 1 };
		GLfloat specCol[4] = { 1.0, 1.0, 1.0, 1 };
		GLfloat ambCol[4] = { 1.0, 1.0, 1.0, 1 };
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffCol );
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specCol );
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 96.0 );
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambCol );	
		glTranslatef(position.getX(), position.getY(), position.getZ());
		glScalef(size, size, size);
		glUseProgram(0); 
		obj->draw();
	}
	glPopMatrix();	
}
void Asteroid::setPosition(Point item){
	position = item;
}
Point Asteroid::getPosition(){
	return position;
}
double Asteroid::getSize(){
	return size;
}