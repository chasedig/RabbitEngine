#version 330 core
out vec4 gl_Position;

out vec3 Normal;
out vec3 FragPosition;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vNormal;

uniform mat4 model, view, projection;

void main()
{
	Normal = mat3(transpose(inverse(model)))* vNormal;
	FragPosition = vec3(model * vec4(position, 1.0));

	gl_Position = projection * view * model * vec4(position, 1.0f);
}