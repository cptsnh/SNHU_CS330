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
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

private:

	// camera variables
	glm::vec3 position{};
	glm::vec3 lookDirection{};
	glm::vec3 upDirection{ 0.f, 1.f, 0.f };
	glm::vec3 rightDirection{ 1.0f, 0.f, 0.f };

	bool isPerspective{ true };

	// camera rotation variables
	float yaw{ -90.f };  // left/right movement
	float pitch{};		// up/down movement

	// perspective variables
	float fov{ 75.f };	// field of view
	float aspectRatio{ 0.f };
	float nearClip{ 0.1f };
	float farClip{ 100.0f };

//	float zoom{75.f};

	int width{ 0 };
	int height{ 0 };

	void recalculateVectors();


public:

	enum class MoveDirection {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	explicit Camera(int w, int h, glm::vec3 initialPosition = glm::vec3{ 0,0,-20.f },
		bool isPerspective = true);

	bool IsPerspective() const { return isPerspective; }
	void SetIsPerspective(bool isPerspective) { this->isPerspective = isPerspective; }
	
	void MoveCamera(MoveDirection direction, float moveAmount);
	void RotateBy(float yaw, float pitch);
	void IncrementZoom(float amount);


	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix() const;

	// for specular
	glm::vec3 GetCamPosition() const { return position; }

	void SetAspectRatio(float aspectRatio) { this->aspectRatio = aspectRatio; }

	void SetSize(int w, int h) {
		this->width = w;
		this->height = h;
	}

};