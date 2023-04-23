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


// in vec2 texCoord;
//uniform sampler2D tex0;	// GL_TEXTURE0
//uniform sampler2D tex1;	// GL_TEXTURE1
//uniform sampler2D tex2; // ...
//uniform sampler2D tex3;


// apr3 - specular
uniform vec3 camPos;

// apr 2
//uniform vec3 lightPos0;
//uniform vec3 lightPos1;

// for point light
uniform PointLight pointLight0;

uniform DirLight dirLight;


// moved from main
vec3 CalcPointLight() {

///	vec3 lightColor = vec3(1.f, 1.f, 1.f); // white
//	vec3 lightColor = vec3(0.f, 1.f, 0.f); // green

	// ambientStr of 0.0 would be no light at all (black screen)
	float ambientStrength = 0.3;
///	vec3 ambient = ambientStrength * lightColor;
	vec3 ambient = ambientStrength * pointLight0.AmbientColor;


	// diffuse
	vec3 norm = normalize(fragNormal);

	// only using 1 light right now, will modify in future
	/// vec3 lightDir = normalize(lightPos0 - fragPosition);
	vec3 lightDir = normalize(pointLight0.Position - fragPosition);


	// helps in determining if objects in front of, opposite direction, perpendicular, etc
	float diff = max(dot(norm, lightDir), 0.0);

	/// vec3 diffuse = diff * lightColor;
	vec3 diffuse = diff * pointLight0.DiffuseColor;


// addition of specular - apr 3
	float specStrength = 0.8;
	float shine = 32;

	vec3 viewDirection = normalize(camPos - fragPosition);
	vec3 reflectDirection = reflect(-lightDir, norm);

	float specV = pow(max(dot(viewDirection, reflectDirection), 0.0), shine);
//	vec3 specColor = specStrength * specV * lightColor;
	vec3 specColor = specStrength * specV * pointLight0.SpecColor;

	float distance = length(pointLight0.Position - fragPosition);
	float attenuation = 1.0 / (pointLight0.ConstantVar + (pointLight0.LinearVar * distance) + (pointLight0.QuadVar * distance * distance) );

	return (diffuse + ambient + specColor) * attenuation;

}

vec3 CalcDirectionLight() {

	// ambientStr of 0.0 would be no light at all (black screen)
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * dirLight.Ambient;

	// diffuse color
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = dirLight.Direction;

	// helps in determining if objects in front of, opposite direction, perpendicular, etc
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 diffuse = diff * dirLight.Diffuse;


// addition of specular - apr 3
//	float specStrength = 0.8f;
//	float shine = 32;
	float specStrength = 1.0f;
	float shine = 128;


	vec3 viewDirection = normalize(camPos - fragPosition);
	vec3 reflectDirection = reflect(-lightDir, norm);

	float specV = pow(max(dot(viewDirection, reflectDirection), 0.0), shine);
	vec3 specColor = specStrength * specV * dirLight.Specular;

	vec3 dirLightColor = (diffuse + ambient + specColor);

	return dirLightColor;

}



void main() {

	vec3 objectColor = vertexColor.xyz;




//	vec3 finalColor = (diffuse + ambient + specColor) * objectColor;
//	vec3 finalColor = dirLightColor * objectColor;

	// for using directional
	//vec3 dlc = CalcDirectionLight();
	//vec3 finalColor = dlc * objectColor;


	// for using point light
	vec3 pl = CalcPointLight();
	vec3 finalColor = pl * objectColor;

	FragColor = vec4(finalColor, 1.0);

}

