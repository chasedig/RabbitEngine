#version 330 core
out vec4 gl_Position;

layout(location = 0) in vec3 position;

uniform mat4 model, view, projection;

void main()
{
	gl_Position = vec4(position, 1.0f);
}