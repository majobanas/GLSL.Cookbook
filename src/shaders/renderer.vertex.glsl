#version 460
in vec3 vertex;
in vec2 uv;

out vec2 UV;

void main()
{
	UV = uv;
	gl_Position = vec4(vertex, 1.0f);
}