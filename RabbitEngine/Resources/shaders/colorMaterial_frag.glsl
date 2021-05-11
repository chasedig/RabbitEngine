#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

struct PointLight
{
	vec3 position;
	vec3 color;
	float power;
};
#define MAX_LIGHTS 4
uniform PointLight pointLights[MAX_LIGHTS];
float PI = 3.1415926;

uniform vec3 color;

float getAttenuatedPower(float lightPower, vec3 lightPosition, vec3 fragPosition)
{
	return (lightPower / (pow(length(lightPosition - fragPosition),2)));
}

vec3 getPointLightDiffuse(vec3 lightPosition, float lightPower, vec3 lightColor, vec3 normal, vec3 fragPosition)
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
	vec3 ambient = getAmbient();

	vec3 totalResult = vec3(0.0f, 0.0f, 0.0f);

	for (int p = 0; p < MAX_LIGHTS; p++)
	{
		vec3 diffuse = getPointLightDiffuse(pointLights[p].position, pointLights[p].power, pointLights[p].color, Normal, FragPosition);

		vec3 result = (diffuse) * color;
		totalResult += result;
	}

	totalResult += ambient;

	FragColor = vec4(totalResult, 1.0);
}