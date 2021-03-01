#version 460
in vec3 worldVertex;
in vec3 worldNormal;
in vec2 UV;

in vec3 viewPosition;
in vec3 reflectedDirection;

uniform float shineness;
uniform sampler2D diffuseTexture;
uniform samplerCube cubemapTexture;
uniform float reflectionFactor;

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
	vec4 textureColor = texture(diffuseTexture, UV);
	vec4 cubemapColor = texture(cubemapTexture, reflectedDirection);
	textureColor = vec4(textureColor.rgb * enlightment, textureColor.a);
	cubemapColor = vec4(cubemapColor.rgb * enlightment, cubemapColor.a);
	fragmentColor = mix(textureColor, cubemapColor, reflectionFactor);
	
}

vec3 Directional(int pI)
{
	sDOTn = max(dot(worldNormal, -light[pI].direction), 0.0f);
	diffuse = sDOTn * light[pI].intensity * light[pI].color;
	
	reflection = 0;
	if (sDOTn > 0.0f) {
		viewDirection = normalize(worldVertex - viewPosition);
		reflectedRayDirection = normalize(viewDirection + lightDirection); //reflect(lightDirection, worldNormal);
		reflection = pow(max(dot(-reflectedRayDirection, worldNormal), 0.0f), shineness);
	}
	specular = reflection * light[pI].color;
	return vec3(0.1f + diffuse + specular);
}

vec3 Point(int pI)
{
	lightDirection = normalize(worldVertex - light[pI].position);
	sDOTn = max(dot(worldNormal, -lightDirection), 0.0f);
	diffuse = sDOTn * light[pI].intensity * light[pI].color;
	
	reflection = 0;
	if (sDOTn > 0.0f) {
		viewDirection = normalize(worldVertex - viewPosition);
		reflectedRayDirection = normalize(viewDirection + lightDirection); //reflect(lightDirection, worldNormal);
		reflection = pow(max(dot(-reflectedRayDirection, worldNormal), 0.0f), shineness);
	}
	specular = reflection * light[pI].color;
	return vec3(0.1f + diffuse + specular);
}

vec3 Spot(int pI)
{
	lightDirection = normalize(worldVertex - light[pI].position);
	sDOTn = max(dot(worldNormal, -lightDirection), 0.0f);
	sDOTv = max(dot(-light[pI].direction, -lightDirection), 0.0f);
	effective = light[pI].effectiveAngle;
	total = light[pI].totalAngle;
	modifier = ((sDOTv - total) / (effective - total));
	diffuse = sDOTn * light[pI].intensity * light[pI].color * modifier;
	
	reflection = 0;
	if (sDOTn > 0.0f) {
		viewDirection = normalize(worldVertex - viewPosition);
		reflectedRayDirection = normalize(viewDirection + lightDirection); //reflect(lightDirection, worldNormal);
		reflection = pow(max(dot(-reflectedRayDirection, worldNormal), 0.0f), shineness);
	}
	specular = reflection * light[pI].color;
	return vec3(0.1f + diffuse + specular);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}