#include "SmallBox.h"


void SmallBox::Initialize()
{
}

void SmallBox::Update(float deltaTime)
{
	//	Transform = glm::rotate(Transform, glm::radians(45.f) * deltaTime, glm::vec3(0, 1, 0));
	//	Transform = glm::rotate(Transform, glm::radians(45.f) * deltaTime, glm::vec3(1, 0, 0));
}

void SmallBox::Draw(const SceneParameters& sceneParms)
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

void SmallBox::createShaders()
{
	Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
	Path textPath = std::filesystem::current_path() / "assets" / "textures";

	this->basicUnlitShader = std::make_shared<Shader>(
		shaderPath / "basicLightNew.vert",
		//		shaderPath / "basicLightNew.frag");
		//		shaderPath / "basicLightNewDirection.frag");
		// shaderPath / "basicLightNewPoint.frag");
		shaderPath / "basicLightNewMulti.frag");


	auto brickTexture = std::make_shared<Texture>(textPath / "container.jpg");
	this->basicUnlitShader->AddTexture(brickTexture);

}


void SmallBox::ProcessLighting(SceneParameters& sceneParms) {

	// return as this is not processing light
	return;
}

void SmallBox::createMesh()
{
	auto smallBox = std::make_shared<Mesh>(PredefinedShapes::smallBoxVertices,
		PredefinedShapes::smallBoxElements,
		glm::vec3(0.5f, 0.5f, 0.5f));

	auto& smallBoxModel = models.emplace_back(smallBox, basicUnlitShader);
	smallBoxModel.GetMesh()->Transform = glm::translate(smallBoxModel.GetMesh()->Transform, glm::vec3(0.0f, 0.25f, 2.0f));
	smallBoxModel.GetMesh()->Transform = glm::scale(smallBoxModel.GetMesh()->Transform, glm::vec3(0.5f, 0.5f, 0.5f));
	smallBoxModel.GetMesh()->Transform = glm::rotate(smallBoxModel.GetMesh()->Transform, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}