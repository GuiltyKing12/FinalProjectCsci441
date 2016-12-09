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

void main() {
    /*****************************************/
    /********* Vertex Calculations  **********/
    /*****************************************/
    vec4 Vertex_new = gl_Vertex;
    // TODO #14: modify our vertex in object space
    gl_Position = gl_ModelViewProjectionMatrix * Vertex_new;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
