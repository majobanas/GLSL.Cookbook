#version 460
in vec3 worldVertex;
in vec3 worldNormal;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 FragPosLightSpace;
} fs_in;

uniform vec3 diffuseColor;
uniform sampler2D shadowMap;

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

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
} 

void main()
{
	for (int i = 0; i < numLights; i++) {
		if (light[i].type == 0) {
			enlightment += Directional(i) * (1.0f - ShadowCalculation(fs_in.FragPosLightSpace));
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
	return	Diffuse(light[pI].direction) * light[pI].intensity * light[pI].color;
}

vec3 Point(int pI) {
	return	Diffuse(normalize(worldVertex - light[pI].position)) * 
			light[pI].intensity * 
			light[pI].color;
}

vec3 Spot(int pI) {
	lightDirection = normalize(worldVertex - light[pI].position);
	sDOTv = max(dot(-light[pI].direction, -lightDirection), 0.0f);
	effective = light[pI].effectiveAngle;
	total = light[pI].totalAngle;

	return	Diffuse(lightDirection) * 
			light[pI].intensity * 
			light[pI].color * 
			((sDOTv - total) / (effective - total));
}

float Diffuse(vec3 pLightDirection) {
	return max(dot(worldNormal, -pLightDirection), 0.0f);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}