#version 460
in vec4 Position;
in vec3 Normal;
in vec2 UV;

uniform sampler2D diffuseTexture;

layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec3 NormalData;
layout (location = 3) out vec3 ColorData;

void main()
{
	PositionData = vec3(Position);
	NormalData = Normal;
	ColorData = texture(diffuseTexture, UV).rgb;
}