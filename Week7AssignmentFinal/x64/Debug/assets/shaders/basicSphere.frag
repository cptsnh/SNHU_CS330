#version 330 core

struct DirLight {

	vec3 Direction;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct PointLight {
	vec3 Position;

	vec3 AmbientColor;
	vec3 DiffuseColor;
	vec3 SpecColor;

	float ConstantVar;
	float LinearVar;
	float QuadVar;
};



out vec4 FragColor;

in vec4 vertexColor;
in vec3 fragNormal;
in vec3 fragPosition;


in vec2 texCoord;
uniform sampler2D tex0;	// GL_TEXTURE0
uniform sampler2D tex1;	// GL_TEXTURE1
uniform sampler2D tex2; // ...
uniform sampler2D tex3;


// for specular
uniform vec3 camPos;

#define MAXPOINTLIGHTS 2	// change this to be the number of lights in scene

// for point light
uniform PointLight pointLights[MAXPOINTLIGHTS];

uniform DirLight dirLight;


// calculations for point light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {

	// ambientStr of 0.0 would be no light at all (black screen)
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * light.AmbientColor;


	// only using 1 light right now, will modify in future
	vec3 lightDir = normalize(light.Position - fragPosition);


	// helps in determining if objects in front of, opposite direction, perpendicular, etc
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.DiffuseColor;


	// addition of specular
	float specStrength = 3.0f; // 1.0;
	float shine = 128; // 32;

	vec3 reflectDirection = reflect(-lightDir, normal);

	float specV = pow(max(dot(viewDir, reflectDirection), 0.0), shine);
	vec3 specColor = specStrength * specV * light.SpecColor;

	float distance = length(light.Position - fragPosition);
	float attenuation = 1.0 / (light.ConstantVar + (light.LinearVar * distance) + (light.QuadVar * distance * distance) );

	return (diffuse + ambient + specColor) * attenuation;

}

// calculations for directional light
vec3 CalcDirectionLight(vec3 normal, vec3 viewDir) {

	// ambientStr of 0.0 would be no light at all (black screen)
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * dirLight.Ambient;

	// diffuse color
	vec3 lightDir = dirLight.Direction;

	// helps in determining if objects in front of, opposite direction, perpendicular, etc
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 diffuse = diff * dirLight.Diffuse;


	// addition of specular
//	float specStrength = 0.8f;
//	float shine = 32;
	float specStrength = 1.0f;
	float shine = 128;


	vec3 reflectDirection = reflect(-lightDir, normal);

	float specV = pow(max(dot(viewDir, reflectDirection), 0.0), shine);
	vec3 specColor = specStrength * specV * dirLight.Specular;

	vec3 dirLightColor = (diffuse + ambient + specColor);

	return dirLightColor;

	// use this to turn off directional light
	// return vec3 (0,0,0);

}



void main() {

	// keep this for using with no texture
	//vec3 objectColor = vertexColor.xyz;

	vec3 objectColor = vec3(vertexColor * texture(tex0, texCoord));


	vec3 norm = normalize(fragNormal);
	vec3 viewDirection = normalize(camPos - fragPosition);

	vec3 result = CalcDirectionLight(norm, viewDirection);



	// for using directional
	//vec3 dlc = CalcDirectionLight();
	//vec3 finalColor = dlc * objectColor;


	// for using point lights
	for (int i = 0; i < MAXPOINTLIGHTS; i++) {
		result += CalcPointLight(pointLights[i], norm, viewDirection);
	}

	vec3 finalColor = result * objectColor;

	FragColor = vec4(finalColor, 1.0);

}

