#pragma once
#include <vector>
#include <glad/glad.h>
#include <types.h>

class Mesh {

private:
	GLuint vbo{};
	GLuint vao{};
	GLuint ebo{};
	GLuint shaderProgram{};

	uint32_t elementCount{0};

	void initialize(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);

	//std::vector<Vertex> vertices;
	//std::vector<uint32_t> elements;

public:
	//Mesh() = default;
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);

	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements, const glm::vec3& color);

	void Draw() const;

	glm::mat4 Transform{ 1.f };
};