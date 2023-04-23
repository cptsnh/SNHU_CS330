#pragma once

#include <projectObject.h>
#include <model.h>

class Plane : public ProjectObject {
private:

	void createShaders();
	void createMesh();

	std::shared_ptr<Shader> basicUnlitShader;
	std::shared_ptr<Mesh> lightMesh{};
	std::vector<Model> models{};

public:
	Plane() {
		createShaders();
		createMesh();
	}


	// Inherited via ProjectObject
	virtual void Initialize() override;

	// rotation can be done here now
	virtual void Update(float deltaTime) override;

	virtual void Draw(const SceneParameters& sceneParms) override;

	virtual void ProcessLighting(SceneParameters& sceneParms) override;

};