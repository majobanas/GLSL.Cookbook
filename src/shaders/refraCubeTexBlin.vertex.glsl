#version 460
in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 matrix;

float eta = 1.0f;

out vec3 worldVertex;
out vec3 worldNormal;
out vec2 UV;

out vec3 viewPosition;
out vec3 reflectedDirection;
out vec3 refractedDirection;

void main()
{

	worldVertex = vec3(matrix * vec4(vertex, 1.0f));
	worldNormal = normalize(vec3(matrix * vec4(normal, 0.0f)));
	UV = uv;
	reflectedDirection = reflect(-normalize(vec3(model[3]) - worldVertex), worldNormal);
	refractedDirection = refract(-normalize(vec3(model[3]) - worldVertex), worldNormal, eta);
	
	viewPosition = vec3(model[3]);

	gl_Position = projection * view * matrix * vec4(vertex, 1.0f);
}