#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D tex0;	// GL_TEXTURE0
uniform sampler2D tex1;	// GL_TEXTURE1
uniform sampler2D tex2; // ...
uniform sampler2D tex3;

void main() {
//	FragColor = texture(tex0, texCoord) * vertexColor;


	// with 0.0, it only does first texture
	// with 1.0, it does the second texture
	// the 0.5 is the weight (even between both textures)
//	FragColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), 0.5) * vertexColor;


	// adding lighting vars

	// ambientStr of 0.0 would be no light at all (black screen)
	float ambientStrength = 0.2;
	vec3 lightColor = vec3(1.f, 1.f, 1.f); // white
//	vec3 lightColor = vec3(0.f, 1.f, 0.f); // green

	vec3 ambient = ambientStrength * lightColor;
	vec3 objectColor = vertexColor.xyz;
	vec3 finalColor = objectColor * ambient;

	FragColor = vec4(finalColor, 1.0);

}

