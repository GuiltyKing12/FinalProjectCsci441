/*
 *   Fragment Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120
uniform sampler2D tex;
void main() {

    /*****************************************/
    /******* Final Color Calculations ********/
    /*****************************************/
    vec4 texel = texture2D( tex, gl_TexCoord[0].st );
    // TODO #10: set the fragment color!
	vec3 ct = texel.rgb;
	float at = texel.a;
    gl_FragColor = vec4(ct, at);
    // TODO #13: use our varying variable
    //gl_FragColor = theColor;
}
