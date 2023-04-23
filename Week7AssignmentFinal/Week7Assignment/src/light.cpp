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


#include "light.h"


void Light::createShaders()
{
	//Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
	//this->basicUnlitShader = std::make_shared<Shader>(
	//	shaderPath / "basicLightNew.vert",
	//	shaderPath / "basicLightNew.frag");


	Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
	this->basicUnlitShader = std::make_shared<Shader>(
		shaderPath / "basicUnlit.vert",
		shaderPath / "basicUnlit.frag");


//	this->basicUnlitShader = std::make_shared<Shader>(Path("basicUnlit.vert"), Path("basicUnlit.frag"));
//	this->basicUnlitShader = std::make_shared<Shader>(Path("basicLightNew.vert"), Path("basicLightNew.frag"));
//	this->basicUnlitShader = std::make_shared<Shader>("basicLightNew.vert", "basicLightNew.frag");
}

void Light::createMesh()
{

	auto cube = std::make_shared<Mesh>(PredefinedShapes::cubeVertices, PredefinedShapes::cubeElements,
		glm::vec3(1.0f, 1.0f, 1.0f));



	auto& cubeModel = models.emplace_back(cube, basicUnlitShader);

//	this->models.emplace_back(cube, this->basicUnlitShader);


	cubeModel.GetMesh()->Transform = glm::scale(cubeModel.GetMesh()->Transform, glm::vec3(0.1f, 0.1f, 0.1f));

}

void Light::Initialize()
{
}

void Light::Update(float deltaTime)
{
	auto cos = std::cos(totalTime);
	auto sin = std::sin(totalTime);

	// decrease the 900 if you want to make it go way out of vision but still get lighting
	Transform = glm::translate(Transform, glm::vec3(cos/2500, 0, sin/2500));
//	Transform = glm::translate(Transform, glm::vec3(0, cos/2500, 0));

	totalTime += deltaTime;
}

void Light::Draw(const SceneParameters& sceneParms)
{
	for (auto& model : models) {
		auto* shader = model.GetShader();
		auto* mesh = model.GetMesh();
		shader->Bind();
		shader->SetMat4("projection", sceneParms.ProjectionMatrix);
		shader->SetMat4("view", sceneParms.ViewMatrix);
		shader->SetMat4("model", Transform * mesh->Transform);

		mesh->Draw();
	}
}


void Light::ProcessLighting(SceneParameters& sceneParms) {
	
	if (sceneParms.Lights.size() < MAXLIGHTS) {

		auto lightPos = glm::vec3(Transform[3]);

		sceneParms.Lights.emplace_back(lightPos);
	}
}


//void Light::Draw2(const glm::mat4& view, const glm::mat4& projection)
//{
//	for (auto& model : models) {
//		auto* shader = model.GetShader();
//		auto* mesh = model.GetMesh();
//		shader->Bind();
//		shader->SetMat4("projection", projection);
//		shader->SetMat4("view", view);
//		shader->SetMat4("model", Transform * mesh->Transform);
//
//		mesh->Draw();
//	}
//}
