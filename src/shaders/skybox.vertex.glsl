#version 460
in vec3 vertex;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 matrix;

out vec3 reflectedDirection;

void main()
{
	reflectedDirection = vertex;

	gl_Position = projection * view * matrix * vec4(vertex, 1.0f);
}