#pragma once

/*
* Author: Chris Trimmer
* Assignment: Week 7 (Final Project)
* Date: 04/14/2023
*
* References:
* Ideas, structure, and support from the following sources:
*   http://www.opengl-tutorial.org/beginners-tutorials/
*   https://www.khronos.org/opengl/wiki/Getting_Started#Tutorials_and_How_To_Guides
*   https://learnopengl.com/Introduction
*   https://www.youtube.com/@snhucomputerscience
*	https://www.songho.ca/opengl/gl_cylinder.html
*/



#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <stb_image.h>

class Texture {

private:
	GLuint textureHandle;


public:
	// path must be const
	explicit Texture(const std::filesystem::path& path);

	void Bind();

};