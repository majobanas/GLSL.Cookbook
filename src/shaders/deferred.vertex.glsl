#version 460
in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 matrix;

out vec4 Position;
out vec3 Normal;
out vec2 UV;

void main()
{
	Position = projection * view * matrix * vec4(vertex, 1.0f);
	Normal = normal;
	UV = uv;

	gl_Position = Position;
}