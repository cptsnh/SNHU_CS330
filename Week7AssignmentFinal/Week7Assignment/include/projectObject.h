#pragma once

#include <glm/glm.hpp>
#include <types.h>

class ProjectObject {

private:

public:
//	ProjectObject() = default;
	~ProjectObject() = default;

	virtual void Initialize() = 0;

	virtual void Update(float deltaTime) = 0;

	virtual void Draw(const SceneParameters& sceneParms) = 0;

	virtual void ProcessLighting(SceneParameters& sceneParms) = 0;

	glm::mat4 Transform{ 1.f };

};