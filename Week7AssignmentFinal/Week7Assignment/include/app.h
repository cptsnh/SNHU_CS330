#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <types.h>
#include <mesh.h>
#include <shader.h>
#include <camera.h>
#include <stb_image.h>
#include <texture.h>
#include <projectObject.h>
#include <light.h>
#include <pointLight.h>
#include <cube.h>
#include <Pyramid.h>
#include <Plane.h>
#include <Cylinder.h>
#include <SmallBox.h>
#include <string>
#include <iostream>
#include <vector>

class App {
private:
	std::string appTitle{};
	int width{};
	int height{};
	bool running{ false };
	float lastFrameTime{ -1.f };

	GLuint matrixTexture;
	GLuint bricksTexture;
	GLuint faceTexture;
	GLuint containerTexture;

	bool firstMouse{ false };
	glm::vec2 lastMousePosition{};
	glm::vec2 cameraLookSpeed{};	// mouse sensitivity

	GLFWwindow* window{ nullptr };

	// control zoom in/out with keys (use 5.f with deltaTime, use 0.1f with const deltaTime local)
	float moveSpeed{ 5.f };
	Camera camera;

	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
//	std::vector<std::unique_ptr<ProjectObject>> projectObjects;
//	std::vector<ProjectObject*> projectObjects;
	std::vector<std::shared_ptr<ProjectObject>> projectObjects;

	Shader shader{};		// no lighting
	Shader shaderUnlit{};	// for diffuse lighting
	Shader shaderLit{};		// for ambient lighting

	Shader shaderLitNew{};

	bool openWindow();
	void processInput(GLFWwindow* window);
	//	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//	void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	void setupScene();
	void update(float deltaTime);
	void draw();
	void setUpInputs();

	void handleInput(float deltaTime);
	

	void mousePositionCallBack(double xpos, double ypos);

	// variables for lighting
	float ambientStr{ 0.1f };
	glm::vec3 ambientColor{ 1.f, 1.f, 1.f };


public:

	// change end parameter to false to force ortho view (true is proj view for 3d game)
	App(std::string title, int w, int h) : appTitle{ title }, width{ w }, height{ h },
		camera{ width, height, {0.f, 0.f, 3.f}, true }, cameraLookSpeed{0.05f, 0.05f}
	{}

	void Run();
	void ChangeSpeed();

};