#version 460
in vec3 worldVertex;
in vec3 worldNormal;
in vec2 UV;

uniform int levels;
const float levelFactor = 1.0f / levels;

uniform vec3 diffuseColor;

uniform int numLights;

uniform struct Light {
	int type;
	vec3 position;
	vec3 color;
	float intensity;
	vec3 direction;
	float totalAngle;
	float effectiveAngle;
} light[64];

vec3 enlightment;

out vec4 fragmentColor;

vec3 Directional(int pI);
vec3 Point(int pI);
vec3 Spot(int pI);

vec3 GammaCorrection(vec3 pColor);

float Diffuse(vec3 pLightDirection);
float Cartoon(float pDiffuse);

float sDOTn;
vec3 lightDirection;
float sDOTv;
float effective;
float total;

void main()
{
	for (int i = 0; i < numLights; i++) {
		if (light[i].type == 0) {
			enlightment += Directional(i);
		}
		if (light[i].type == 1) {
			enlightment += Point(i);
		}
		if (light[i].type == 2) {
			enlightment += Spot(i);
		}
	}
	fragmentColor = vec4(diffuseColor * enlightment, 1.0f);
}

vec3 Directional(int pI) {
	return	Cartoon(Diffuse(light[pI].direction)) * 
			light[pI].intensity * 
			light[pI].color;
}

vec3 Point(int pI) {
	return	Cartoon(Diffuse(normalize(worldVertex - light[pI].position))) * 
			light[pI].intensity * 
			light[pI].color;
}

vec3 Spot(int pI) {
	lightDirection = normalize(worldVertex - light[pI].position);
	sDOTv = max(dot(-light[pI].direction, -lightDirection), 0.0f);
	effective = light[pI].effectiveAngle;
	total = light[pI].totalAngle;

	return	Cartoon(Diffuse(lightDirection)) * 
			light[pI].intensity * 
			light[pI].color * 
			((sDOTv - total) / (effective - total));
}

float Diffuse(vec3 pLightDirection) {
	return max(dot(worldNormal, -pLightDirection), 0.0f);
}

float Cartoon(float pDiffuse) {
	return floor(pDiffuse * levels) * levelFactor;
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}