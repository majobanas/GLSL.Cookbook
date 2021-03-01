#version 460
in vec3 worldVertex;
in vec3 worldNormal;
in vec2 UV;

in vec3 viewPosition;

uniform sampler2D diffuseTexture;
uniform samplerCube cubemapTexture;

out vec4 fragmentColor;

vec3 schlickFresnel(float pDot);

vec3 GammaCorrection(vec3 pColor);

void main()
{
	vec3 n = normalize(worldNormal);
	vec3 v = normalize(viewPosition - worldVertex);

	vec3 light = texture(cubemapTexture, n).rgb;
	vec3 color = texture(diffuseTexture, UV).rgb;
	color = pow(color, vec3(2.2f));
    color = light * color * (1.0f - schlickFresnel(dot(n, v)));
	color *= light;

	color = GammaCorrection(color);
	fragmentColor = vec4(color, 1.0f);
}

vec3 schlickFresnel(float pDot) {
  vec3 f0 = vec3(0.04f);
  return f0 + (1.0f - f0) * pow(1.0f - pDot, 5);
}

vec3 GammaCorrection(vec3 pColor) {
	return pow(pColor, vec3(1.0f / 2.2f));
}