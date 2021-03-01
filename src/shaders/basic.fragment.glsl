#version 460
uniform vec3 diffuseColor;

out vec4 fragmentColor;

vec3 GammaCorrection(vec3 pColor);

void main()
{
    fragmentColor = vec4(diffuseColor, 1.0);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}