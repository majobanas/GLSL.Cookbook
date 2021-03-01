#version 460
in vec3 vertex;
in vec2 uv;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 matrix;

out vec2 UV;

void main()
{
	UV = uv;
	gl_Position = projection * view * matrix * vec4(vertex, 1.0f);
}