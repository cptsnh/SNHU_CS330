#pragma once

#include <mesh.h>
#include <shader.h>

class Model {
private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Mesh> mesh;

public:
	Model(std::shared_ptr<Mesh> m, std::shared_ptr<Shader> s) :
		mesh{ m }, shader{ s } {}
	Shader* GetShader() { return shader.get(); }
	Mesh* GetMesh() { return mesh.get(); }

};