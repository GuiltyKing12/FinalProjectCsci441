/*
 *   Fragment Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

uniform sampler2D tex0;
varying vec4 Vertex_UV;
const float PI = 3.1415926535;

void main() {
    //vec4 texel = texture2D( tex, gl_TexCoord[0].st );
    // TODO #10: set the fragment color!
    //vec3 ct = texel.rgb;
    //float at = texel.a;
    //gl_FragColor = vec4(ct, at);
    // TODO #13: use our varying variable
    //gl_FragColor = theColor;
    float aperture = 178.0;
    float apertureHalf = 0.5 * aperture * (PI / 180.0);
    float maxFactor = sin(apertureHalf);
    
    vec2 uv;
    vec2 xy = 2.0 * Vertex_UV.xy - 1.0;
    float d = length(xy);
    if (d < (2.0-maxFactor))
    {
        d = length(xy * maxFactor);
        float z = sqrt(1.0 - d * d);
        float r = atan(d, z) / PI;
        float phi = atan(xy.y, xy.x);
        
        uv.x = r * cos(phi) + 0.5;
        uv.y = r * sin(phi) + 0.5;
    }
    else
    {
        uv = Vertex_UV.xy;
    }
    vec4 c = texture2D(tex0, uv);
    gl_FragColor = c;
}
