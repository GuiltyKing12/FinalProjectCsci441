/*
 *   Fragment Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

uniform sampler2D tex;
uniform float ratio;

void main() {
    vec4 texel = texture2D( tex, gl_TexCoord[0].st );
    vec3 ct = texel.rgb;
    ct.r += (1-ratio);
    float at = texel.a;
    gl_FragColor = vec4(ct, at);
}
