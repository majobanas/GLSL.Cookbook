#version 460
in vec3 vertex;
in vec3 normal;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 matrix;
uniform mat4 lightViewProjection;

out vec3 worldVertex;
out vec3 worldNormal;

void main()
{
    vs_out.FragPos = vec3(matrix * vec4(vertex, 1.0));
    vs_out.Normal = transpose(inverse(mat3(matrix))) * normal;
    vs_out.FragPosLightSpace = lightViewProjection * vec4(vs_out.FragPos, 1.0);

	worldVertex = vec3(matrix * vec4(vertex, 1.0f));
	worldNormal = normalize(vec3(matrix * vec4(normal, 0.0f)));

	gl_Position = projection * view * matrix * vec4(vertex, 1.0f);
}