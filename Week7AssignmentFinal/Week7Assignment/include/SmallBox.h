#pragma once

#include <projectObject.h>
#include <model.h>

class SmallBox : public ProjectObject {
private:

	void createShaders();
	void createMesh();

	std::shared_ptr<Shader> basicUnlitShader;

	std::unique_ptr<Shader> testShader;

	std::shared_ptr<Mesh> lightMesh{};
	std::vector<Model> models{};

public:
	SmallBox() {
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