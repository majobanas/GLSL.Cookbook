#version 460
in vec2 UV;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D colorTexture;

layout (location = 0) out vec4 fragmentColor;

vec3 GammaCorrection(vec3 pColor);

void main()
{
	fragmentColor = vec4(texture(colorTexture, UV).rgb, 1.0f);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}