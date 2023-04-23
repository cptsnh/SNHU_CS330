#pragma once

#include<iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <texture.h>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using Path = std::filesystem::path;

class Shader {

private:
	
	void load(const std::string& vertexSource, const std::string& fragmentSource);
	GLuint shaderProgram;
	GLint getUniformLocation(const std::string& uniformName) const;

	std::vector<std::shared_ptr<Texture>> textures;

	void setTextures();

public:

	static inline Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";

	Shader() = default;
	Shader(const std::string& vertexSource, const std::string& fragmentSource);
	Shader(const Path& vertexPath, const Path& fragmentPath);

//	Shader(Path vertexPath, Path fragmentPath);

	void Bind();

	void SetMat4(const std::string& uniformName, const glm::mat4& mat4) const;
	void SetInt(const std::string& uniformName, int value) const;


	// new vars for lighting
	void SetVec3(const std::string& uniformName, const glm::vec3& vec3) const;
	void SetFloat(const std::string& uniformName, const float value) const;

	void AddTexture(const std::shared_ptr<Texture>& texture);
	
};
