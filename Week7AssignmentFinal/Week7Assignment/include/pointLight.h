#pragma once
#include <projectObject.h>
#include <memory>
#include <mesh.h>
#include <shader.h>
#include <model.h>

class PointLight : public ProjectObject {

private:

	//std::shared_ptr<Mesh> cylinder;
	//std::shared_ptr<Mesh> cube;
	//std::shared_ptr<Mesh> pyramid;

	// glm::mat4 Transform{ 1.f };   // moved to model class

	std::shared_ptr<Shader> basicUnlitShader{};
	std::shared_ptr<Mesh> lightMesh{};
	std::vector<Model> models{};

	void createShaders();
	void createMesh();

	float totalTime{ 1.f };

public:
	PointLight() {
		createShaders();
		createMesh();
	}


	glm::vec3 AmbientColor{};
	glm::vec3 DiffuseColor{};
	glm::vec3 SpecColor{};

	float ConstantVar{ 0.f };
	float LinearVar{ 0.f };
	float QuadVar{ 0.f };



	// Inherited via ProjectObject
	virtual void Initialize() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw(const SceneParameters& sceneParms) override;

	virtual void ProcessLighting(SceneParameters& sceneParms) override;
};