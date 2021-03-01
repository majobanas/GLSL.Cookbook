#version 460
in vec3 reflectedDirection;

uniform samplerCube cubemapTexture;

vec3 GammaCorrection(vec3 pColor);

out vec4 fragmentColor;

void main()
{
	fragmentColor = texture(cubemapTexture, reflectedDirection);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 1.0f));
}