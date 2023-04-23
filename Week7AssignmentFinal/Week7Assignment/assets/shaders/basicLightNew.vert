
#version 330 core
layout (location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

out vec4 vertexColor;
out vec3 fragNormal;
out vec3 fragPosition;
out vec2 texCoord;          // comment this out for only doing lights with no texture

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() {
//    gl_Position = vec4(position.x, position.y, position.z, 1.0f);

    gl_Position = projection * view * model * vec4(position, 1);
    fragPosition = vec3(model * vec4(position, 1));
    vertexColor = vec4(color, 1.0f);
//  apr 2 works  fragNormal = normal;

//  apr 3 new -- for proper lighting (although maybe not permanent solution)
    fragNormal = mat3(transpose(inverse(model))) * normal;

    // for only doing lights, comment this out
    texCoord = uv;
}
