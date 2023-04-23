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
	FragColor = mix(texture(tex2, texCoord), texture(tex3, texCoord), 1.0) * vertexColor;
}

