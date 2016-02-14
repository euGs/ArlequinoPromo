#version 150

uniform vec4 globalColor;
uniform sampler2DRect source;
uniform vec2 direction;
uniform float distribution = 9.f;
uniform float kernelSize;

uniform float M_PI = 3.14159265358979323846264338327950288;

in vec2 texCoordVarying;

out vec4 fragColor;

void weight(in float x, in float d, out float w){
    w = 1.f / ( sqrt(2*M_PI*d*d) ) * ( exp(-(x*x)/(2*d*d)) );
}

void main() {
    float w = 1.f;
    weight(0, distribution, w);
    float weightedSum = w;
    
    fragColor = texture(source, texCoordVarying) * w;
    
    // Calculate sum of weights.
    for (float i=1; i<kernelSize; i++) {
        weight(i, distribution, w);
        weightedSum += w*2;
    }
    
    for (float i=1; i<kernelSize; i++) {
        weight(i, distribution, w);
        fragColor += texture(source, texCoordVarying + direction*i) * w / weightedSum;
        
        fragColor += texture(source, texCoordVarying - direction*i) * w / weightedSum;
    }
}