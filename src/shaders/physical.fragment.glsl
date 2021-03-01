#version 460
in vec3 worldVertex;
in vec3 worldNormal;

in vec3 viewPosition;

uniform vec3 diffuseColor;
uniform float roughness;
uniform bool metal;

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

float RAD_PI = 3.1415926535897932384626433832795f;

out vec4 fragmentColor;

vec3 SchlickFresnel(float lDOTh);
float GeomSmith(float pDot);
float ggxDistribution(float nDOTh);
vec3 microfacetModel(int pI, vec3 pPosition, vec3 pNormal);

vec3 GammaCorrection(vec3 pColor);

void main() {
	vec3 sum = vec3(0.0f);
	vec3 normal = normalize(worldNormal);

	for (int i = 0; i < numLights; i++) {
		sum += microfacetModel(i, worldVertex, normal);
	}

	fragmentColor = vec4(GammaCorrection(sum), 1.0f);
}

vec3 SchlickFresnel(float lDOTh) {
	vec3 f0 = vec3(0.04); // Dielectrics
	if (metal) {
		f0 = diffuseColor;
	}
	return f0 + (1 - f0) * pow(1.0f - lDOTh, 5);
}

float GeomSmith(float pDot) {
	float k = (roughness + 1.0f) * (roughness + 1.0f) / 0.8f;
	float denom = pDot * (1 - k) + k;
	return 1.0f / denom;
}

float ggxDistribution(float nDOTh) {
	float alpha2 = roughness * roughness * roughness * roughness;
	float d = (nDOTh * nDOTh) * (alpha2 - 1.0f) + 1.0f;
	return alpha2 / (RAD_PI * d * d);
}

vec3 microfacetModel(int pI, vec3 pPosition, vec3 pNormal) {
	vec3 diffuseBRDF = vec3(0.0f); // Metallic
	if (!metal) {
		diffuseBRDF = diffuseColor;
	}
	vec3 l = vec3(0.0f);
	vec3 lightI = vec3(light[pI].intensity) * light[pI].color;
	if (light[pI].type == 0) { //  Directional light
		l = normalize(-light[pI].direction);
	} 
	//else if (light[pI].type == 2) {
	//	l = light[pI].position - pPosition;
	//} 
	else { // Positional light
		l = light[pI].position - pPosition;
		float dist = length(l);
		l = normalize(l);
		lightI /= (dist * dist);
	}
	vec3 v = -normalize(pPosition - viewPosition);
	vec3 h = normalize(v + l);
	float nDOTh = dot(pNormal, h);
	float lDOTh = dot(l, h);
	float nDOTl = max(dot(pNormal, l), 0.0f);
	float nDOTv = dot(pNormal, v);
	//float modifier = 1.0f;
	//if (light[pI].type == 2) {
	//	float effective = light[pI].effectiveAngle;
	//	float total = light[pI].totalAngle;
	//	float lDOTv = max(dot(l, -light[pI].direction), 0.0f);
	//	modifier = ((lDOTv - total) / (effective - total));
	//}
	vec3 specularBRDF = 0.25f * 
						ggxDistribution(nDOTh) * 
						SchlickFresnel(lDOTh) *
						GeomSmith(nDOTl) *
						GeomSmith(nDOTv);
	return (diffuseBRDF + RAD_PI * specularBRDF) * lightI * nDOTl;// * modifier;
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}

