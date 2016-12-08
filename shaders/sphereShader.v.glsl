/*
 *   Vertex Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

uniform mat4 ProjectionModelviewMatrix;
uniform int distort;
uniform float time;
varying vec4 Vertex_UV;

void main() {
    /*****************************************/
    /********* Vertex Calculations  **********/
    /*****************************************/
    vec4 Vertex_new = gl_Vertex;
    // TODO #14: modify our vertex in object space
    if(distort == 1) {
        Vertex_new = gl_Vertex + ((1.8 * (sin(time) + 1) / 100) - .01);
    }
    gl_Position = gl_ModelViewProjectionMatrix * Vertex_new;
    Vertex_UV = gl_MultiTexCoord0;
}
