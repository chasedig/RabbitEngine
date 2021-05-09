#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

uniform vec3 color;

float getAttenuatedPower(float lightPower, vec3 lightPosition, vec3 fragPosition)
{
	return lightPower * (1 / length(lightPosition - fragPosition));
}

vec3 getDiffuse(vec3 lightPosition, float lightPower, vec3 lightColor, vec3 normal, vec3 fragPosition)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	float attenuatedPower = getAttenuatedPower(lightPower, lightPosition, fragPosition);
	vec3 diffuse = attenuatedPower * diff * lightColor;
	return diffuse;
}

vec3 getAmbient()
{
	vec3 ambientColor = vec3(1.0, 1.0, 1.0);
	return ambientColor * 0.1;
}

void main()
{
	vec3 lightPosition = vec3(0.0, 10.0, -10.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	float lightPower = 20;

	//vec3 ambient = lightPower * 1/length(lightPosition - FragPosition) * lightColor;

	vec3 diffuse = getDiffuse(lightPosition, lightPower, lightColor, Normal, FragPosition);
	vec3 ambient = getAmbient();

	vec3 result = (ambient + diffuse) * color;

	FragColor = vec4(result, 1.0);
}