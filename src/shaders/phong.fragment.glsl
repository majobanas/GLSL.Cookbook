#version 460
in vec3 worldVertex;
in vec3 worldNormal;

in vec3 viewPosition;
in vec3 viewDir;

uniform float shineness;
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

float sDOTn;
vec3 lightDirection;
float sDOTv;
float effective;
float total;
float modifier;
vec3 diffuse;
float reflection;
vec3 viewDirection;
vec3 reflectedRayDirection;
vec3 specular;

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

vec3 Directional(int pI)
{
	sDOTn =		Diffuse(light[pI].direction);
	diffuse =	sDOTn * 
				light[pI].intensity * 
				light[pI].color;
	
	reflection = 0;
	if (sDOTn > 0.0f) {
		viewDirection = normalize(worldVertex - viewPosition);
		reflectedRayDirection = reflect(light[pI].direction, worldNormal);
		reflection = pow(max(dot(reflectedRayDirection, -viewDirection), 0.0f), shineness);
	}
	specular = reflection * light[pI].color;
	return vec3(0.1f + diffuse + specular);
}

vec3 Point(int pI)
{
	lightDirection = normalize(worldVertex - light[pI].position);
	sDOTn =		Diffuse(lightDirection);
	diffuse =	sDOTn * 
				light[pI].intensity * 
				light[pI].color;
	
	reflection = 0;
	if (sDOTn > 0.0f) {
		viewDirection = normalize(worldVertex - viewPosition);
		reflectedRayDirection = reflect(lightDirection, worldNormal);
		reflection = pow(max(dot(reflectedRayDirection, -viewDirection), 0.0f), shineness);
	}
	specular = reflection * light[pI].color;
	return vec3(0.1f + diffuse + specular);
}

vec3 Spot(int pI)
{
	lightDirection = normalize(worldVertex - light[pI].position);
	sDOTn = Diffuse(lightDirection);
	sDOTv = max(dot(-light[pI].direction, -lightDirection), 0.0f);
	effective = light[pI].effectiveAngle;
	total = light[pI].totalAngle;
	modifier = ((sDOTv - total) / (effective - total));
	diffuse =	sDOTn * 
				light[pI].intensity *	
				light[pI].color * 
				modifier;
	
	reflection = 0;
	if (sDOTn > 0.0f) {
		viewDirection = normalize(worldVertex - viewPosition);
		reflectedRayDirection = reflect(lightDirection, worldNormal);
		reflection = pow(max(dot(reflectedRayDirection, -viewDirection), 0.0f), shineness);
	}
	specular = reflection * light[pI].color;
	return vec3(0.1f + diffuse + specular);
}

float Diffuse(vec3 pLightDirection) {
	return max(dot(worldNormal, -pLightDirection), 0.0f);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}