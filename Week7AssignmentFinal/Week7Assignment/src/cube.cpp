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


#include "Cube.h"


void Cube::Initialize()
{
}

void Cube::Update(float deltaTime)
{
	//	Transform = glm::rotate(Transform, glm::radians(45.f) * deltaTime, glm::vec3(0, 1, 0));
	//	Transform = glm::rotate(Transform, glm::radians(45.f) * deltaTime, glm::vec3(1, 0, 0));
}

void Cube::Draw(const SceneParameters& sceneParms)
{

	Shader* lastShader = nullptr;

	for (auto& model : this->models) {
		auto* shader = model.GetShader();
		auto* mesh = model.GetMesh();

		if (shader != lastShader) {

			shader->Bind();
			shader->SetMat4("projection", sceneParms.ProjectionMatrix);
			shader->SetMat4("view", sceneParms.ViewMatrix);


			// establish camPosition for specular ("camPosition" is variable in frag)
			shader->SetVec3("camPos", sceneParms.CamPosition);


			// use this for diffuse lighting
			// deal light data for diffuse
			//for (auto i = 0; i < sceneParms.Lights.size() && i < MAXLIGHTS; i++) {
			//	std::string uniformName = "lightPos";
			//	uniformName += std::to_string(i);

			//	shader->SetVec3(uniformName, sceneParms.Lights[i]);

			//}

			// for point lighting
			for (auto i = 0; i < sceneParms.Lights.size() && i < MAXPOINTLIGHTS; i++) {

				// need to make sure name is correct for array syntax -- see below				
//				std::string baseUniformName = "pointLight";
//				baseUniformName += std::to_string(i);  // we named it pointLight0 in frag

				std::string baseUniformName = "pointLights[";
				baseUniformName += std::to_string(i) + "]";


				// shader value in struct		// sceneParm value
				shader->SetVec3(baseUniformName + ".Position", sceneParms.Lights[i].Position);
				shader->SetVec3(baseUniformName + ".AmbientColor", sceneParms.Lights[i].AmbientColor);
				shader->SetVec3(baseUniformName + ".DiffuseColor", sceneParms.Lights[i].DiffuseColor);
				shader->SetVec3(baseUniformName + ".SpecColor", sceneParms.Lights[i].SpecColor);

				shader->SetFloat(baseUniformName + ".ConstantVar", sceneParms.Lights[i].ConstantVar);
				shader->SetFloat(baseUniformName + ".LinearVar", sceneParms.Lights[i].LinearVar);
				shader->SetFloat(baseUniformName + ".QuadVar", sceneParms.Lights[i].QuadVar);

			}

			// for diffuse in directional frag
			shader->SetVec3("dirLight.Direction", sceneParms.DirLight.Direction);
			shader->SetVec3("dirLight.Diffuse", sceneParms.DirLight.DiffuseColor);
			shader->SetVec3("dirLight.Ambient", sceneParms.DirLight.AmbientColor);
			shader->SetVec3("dirLight.Specular", sceneParms.DirLight.SpecColor);

		}

		shader->SetMat4("model", Transform * mesh->Transform);

		mesh->Draw();
	}
}

void Cube::createShaders()
{
	Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
	Path textPath = std::filesystem::current_path() / "assets" / "textures";

	this->basicUnlitShader = std::make_shared<Shader>(
		shaderPath / "basicLightNew.vert",
		//		shaderPath / "basicLightNew.frag");
		//		shaderPath / "basicLightNewDirection.frag");
		// shaderPath / "basicLightNewPoint.frag");
		shaderPath / "basicLightNewMulti.frag");


	auto texture = std::make_shared<Texture>(textPath / "matrix.jpg");
	this->basicUnlitShader->AddTexture(texture);
}


void Cube::ProcessLighting(SceneParameters& sceneParms) {

	// return as this is not processing light
	return;
}

void Cube::createMesh()
{

	auto cube = std::make_shared<Mesh>(PredefinedShapes::cubeVertices,
		PredefinedShapes::cubeElements,
		glm::vec3(0.5f, 0.5f, 0.5f));

	auto& cubeModel = models.emplace_back(cube, basicUnlitShader);
	cubeModel.GetMesh()->Transform = glm::translate(cubeModel.GetMesh()->Transform, glm::vec3(2.0f, 0.5f, -0.5f));
	cubeModel.GetMesh()->Transform = glm::scale(cubeModel.GetMesh()->Transform, glm::vec3(0.25f, 0.25f, 0.25f));
//	cubeModel.GetMesh()->Transform = glm::rotate(cubeModel.GetMesh()->Transform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

}