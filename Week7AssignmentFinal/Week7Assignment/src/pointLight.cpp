#include "pointLight.h"


void PointLight::createShaders()
{
	Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
	this->basicUnlitShader = std::make_shared<Shader>(
		shaderPath / "basicUnlit.vert",
		shaderPath / "basicUnlit.frag");

}

// create the light as a cube
void PointLight::createMesh()
{
	auto cube = std::make_shared<Mesh>(PredefinedShapes::cubeVertices, PredefinedShapes::cubeElements,
		glm::vec3(1.0f, 1.0f, 1.0f));

	auto& cubeModel = models.emplace_back(cube, basicUnlitShader);

	// make light models unseeable
	cubeModel.GetMesh()->Transform = glm::scale(cubeModel.GetMesh()->Transform, glm::vec3(0.0f, 0.0f, 0.0f));
//	cubeModel.GetMesh()->Transform = glm::scale(cubeModel.GetMesh()->Transform, glm::vec3(0.1f, 0.1f, 0.1f));

}

void PointLight::Initialize()
{
}

void PointLight::Update(float deltaTime)
{
	auto cos = std::cos(totalTime);
	auto sin = std::sin(totalTime);

	// decrease the 900 if you want to make it go way out of vision but still get lighting
//	Transform = glm::translate(Transform, glm::vec3(cos/2500, 0, sin/2500));
//	Transform = glm::translate(Transform, glm::vec3(0, cos/2500, 0));

//	Transform = glm::translate(Transform, glm::vec3(cos / 900, 0, sin / 900));
//	Transform = glm::translate(Transform, glm::vec3(0, cos / 900, 0));


	totalTime += deltaTime;
}

void PointLight::Draw(const SceneParameters& sceneParms)
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


void PointLight::ProcessLighting(SceneParameters& sceneParms) {
	
	if (sceneParms.Lights.size() < MAXLIGHTS) {

		// translate vars with shader
		PointLightStruct pointLight{
			.Position = glm::vec3(Transform[3]),
			.AmbientColor = AmbientColor,
			.DiffuseColor = DiffuseColor,
			.SpecColor = SpecColor,
			.ConstantVar = ConstantVar,
			.LinearVar = LinearVar,
			.QuadVar = QuadVar
		};

	//	auto lightPos = glm::vec3(Transform[3]);

		sceneParms.Lights.emplace_back(pointLight);
	}
}

