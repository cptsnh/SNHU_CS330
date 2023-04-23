#pragma once
#include <projectObject.h>
#include <memory>
#include <mesh.h>
#include <shader.h>
#include <model.h>

class Light : public ProjectObject {

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

	float totalTime{ 3.f };

public:
	Light() {
		createShaders();
		createMesh();
	}


	// Inherited via ProjectObject
	virtual void Initialize() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw(const SceneParameters& sceneParms) override;

	virtual void ProcessLighting(SceneParameters& sceneParms) override;
};