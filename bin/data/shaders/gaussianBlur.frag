#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect source;
uniform vec2 direction;
uniform float distribution = 9;
uniform float kernelSize;
uniform float brightness = 1;

uniform float M_PI = 3.14159265358979323846264338327950288;

void weight(in float x, in float d, out float w){
    w = 1.f / ( sqrt(2*M_PI*d*d) ) * ( exp(-(x*x)/(2*d*d)) );
}

void main() {
    float w = 1.f;
    weight(0, distribution, w);
    float weightedSum = w;
    
    vec2 texCoord = gl_TexCoord[0].st;
    gl_FragColor = texture2DRect(source, texCoord) * w;
    
    // Calculate sum of weights.
    for (float i=1; i<kernelSize; i++) {
        weight(i, distribution, w);
        weightedSum += w*2;
    }
    
    for (float i=1; i<kernelSize; i++) {
        weight(i, distribution, w);
        gl_FragColor += texture2DRect(source, texCoord + direction*i) * w / weightedSum;
        
        gl_FragColor += texture2DRect(source, texCoord - direction*i) * w / weightedSum;
    }
    
    gl_FragColor *= brightness;
}