#version 460
in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 matrix;

out vec3 worldVertex;
out vec3 worldNormal;
out vec2 UV;

out vec3 viewPosition;
out vec3 reflectedDirection;

void main()
{

	worldVertex = vec3(matrix * vec4(vertex, 1.0f));
	worldNormal = normalize(vec3(matrix * vec4(normal, 0.0f)));
	UV = uv;
	reflectedDirection = reflect(-normalize(vec3(model[3]) - worldVertex), worldNormal);
	viewPosition = vec3(model[3]);

	gl_Position = projection * view * matrix * vec4(vertex, 1.0f);
}