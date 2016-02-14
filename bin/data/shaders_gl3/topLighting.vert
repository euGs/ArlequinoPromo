#version 150

uniform mat4 modelViewProjectionMatrix;

uniform float toplightStartY;
uniform float toplightIntensity;
uniform float topLightEndY;
uniform float ambientLight;

in vec4 position;
in vec2 texcoord;

out float brightness;
out vec2 texCoordVarying;

void main() {
    float y = (modelViewProjectionMatrix * position).y;
    float distanceNormalised = (y-topLightEndY)/(toplightStartY-topLightEndY);
    brightness = ambientLight + toplightIntensity * distanceNormalised;
    
    texCoordVarying = texcoord;
    
    gl_Position = modelViewProjectionMatrix * position;
}