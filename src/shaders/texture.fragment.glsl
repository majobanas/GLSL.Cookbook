#version 460
in vec2 UV;

uniform sampler2D diffuseTexture;

out vec4 fragmentColor;

vec3 GammaCorrection(vec3 pColor);

void main()
{
	fragmentColor = texture(diffuseTexture, UV);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}