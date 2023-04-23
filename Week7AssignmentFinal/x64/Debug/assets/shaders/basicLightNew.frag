#version 330 core
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
uniform vec3 lightPos0;
uniform vec3 lightPos1;



void main() {
//	FragColor = texture(tex0, texCoord) * vertexColor;


	// with 0.0, it only does first texture
	// with 1.0, it does the second texture
	// the 0.5 is the weight (even between both textures)
//	FragColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), 0.5) * vertexColor;


	// adding lighting vars for diffuse + ambient
	//
	//
	//

	vec3 objectColor = vertexColor.xyz;
//	vec3 lightColor = vec3(1.f, 1.f, 1.f); // white
	vec3 lightColor = vec3(0.f, 1.f, 0.f); // green

	// ambientStr of 0.0 would be no light at all (black screen)
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(fragNormal);

	// only using 1 light right now, will modify in future
	vec3 lightDir = normalize(lightPos0 - fragPosition);

	// helps in determining if objects in front of, opposite direction, perpendicular, etc
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 diffuse = diff * lightColor;


// addition of specular - apr 3
	float specStrength = 0.8;
	float shine = 32;

	vec3 viewDirection = normalize(camPos - fragPosition);
	vec3 reflectDirection = reflect(-lightDir, norm);

	float specV = pow(max(dot(viewDirection, reflectDirection), 0.0), shine);
	vec3 specColor = specStrength * specV * lightColor;


//	vec3 finalColor = objectColor * ambient;
//	vec3 finalColor = (diffuse + ambient) * objectColor;

	vec3 finalColor = (diffuse + ambient + specColor) * objectColor;
	FragColor = vec4(finalColor, 1.0);

}

