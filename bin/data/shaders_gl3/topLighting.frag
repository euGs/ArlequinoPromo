#version 150

uniform vec4 globalColor;
uniform sampler2DRect tex0;
uniform float alpha;

in float brightness;
in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    vec4 texel = texture(tex0, texCoordVarying);
    outputColor = vec4(texel.rgb*brightness, alpha);
}