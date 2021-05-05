#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

uniform vec3 color;

void main()
{
	vec3 lightPosition = vec3(0.0, 10.0, 0.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	vec3 ambient = 0.1 * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = ((ambient + diffuse) * color);

	FragColor = vec4(result, 1.0);
}