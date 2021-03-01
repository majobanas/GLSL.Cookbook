#version 460
in vec3 worldVertex;
in vec3 worldNormal;
in vec2 UV;

in vec3 viewPosition;

uniform int pass;

uniform vec3 edgeColor;
uniform float shineness;

uniform sampler2D renderTexture;
uniform sampler2D diffuseTexture;

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

const float threshold = 1.0f;
const vec3 lum = vec3(0.2126f, 0.7152f, 0.0722f);

out vec4 fragmentColor;

float luminance(vec3 pColor);
vec4 pass1();
vec4 pass2();

bool isEdge();
vec4 blinn();

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

void main() {
	if (pass == 1) fragmentColor = pass1();
	if (pass == 2) fragmentColor = pass2();
}

float luminance(vec3 pColor) {
	return dot(lum, pColor);
}

vec4 pass1() {
	return vec4(vec3(gl_FragCoord.z), 1.0f);
}

vec4 pass2() {
    if(isEdge())
        return vec4(edgeColor, 1.0f);
    else
        return blinn();
}

bool isEdge() {
    ivec2 pix = ivec2(gl_FragCoord.xy);

    float s00 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(-1,1)).rgb);
    float s10 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(-1,0)).rgb);
    float s20 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(-1,-1)).rgb);
    float s01 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(0,1)).rgb);
    float s21 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(0,-1)).rgb);
    float s02 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(1,1)).rgb);
    float s12 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(1,0)).rgb);
    float s22 = luminance(texelFetchOffset(renderTexture, pix, 0, ivec2(1,-1)).rgb);

    float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
    float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);

    float g = sx * sx + sy * sy;
    return g > threshold;
}

vec4 blinn() {
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

    vec4 diffuseColor = texture(diffuseTexture, UV);
    return vec4(diffuseColor.rgb * enlightment, diffuseColor.a);
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