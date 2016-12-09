/*
 *   Vertex Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

uniform mat4 ProjectionModelviewMatrix;
uniform int distort;
uniform float time;
uniform float ratio;

varying vec3 N;
varying vec3 v;

void main() {
    /*****************************************/
    /********* Vertex Calculations  **********/
    /*****************************************/
    vec4 Vertex_new = gl_Vertex;
    if(1-ratio > .88) Vertex_new = gl_Vertex + (1-ratio);
    // TODO #14: modify our vertex in object space
    v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 
}
