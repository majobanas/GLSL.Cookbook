#version 460
in vec3 vertex;
in vec3 normal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 matrix;

out vec3 worldVertex;
out vec3 worldNormal;

out vec3 viewPosition;

void main()
{

	worldVertex = vec3(matrix * vec4(vertex, 1.0f));
	worldNormal = normalize(vec3(matrix * vec4(normal, 0.0f)));

	viewPosition = vec3(inverse(view)[3]);

	gl_Position = projection * view * matrix * vec4(vertex, 1.0f);
}