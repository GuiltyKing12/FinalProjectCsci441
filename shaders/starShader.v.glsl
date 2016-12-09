/*
 *   Vertex Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

uniform float life;
uniform float maxLife;

void main() {
    /*****************************************/
    /********* Vertex Calculations  **********/
    /*****************************************/
    
    vec4 Vertex_new = gl_Vertex;
    float lifeTime = life / maxLife;
    // TODO #14: modify our vertex in object space
    Vertex_new.x *= lifeTime;
	Vertex_new.y *= lifeTime;
	Vertex_new.z *= lifeTime;
    gl_Position = gl_ModelViewProjectionMatrix * Vertex_new;
	/*****************************************/
    /********* Texture Calculations  *********/
    /*****************************************/

    // pass the texture coordinate through to the fragment processor
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
