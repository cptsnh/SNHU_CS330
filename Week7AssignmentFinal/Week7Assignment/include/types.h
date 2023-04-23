#pragma once
#include <glm/glm.hpp>
#include <vector>

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


constexpr uint8_t MAXLIGHTS = 5;
constexpr uint8_t MAXPOINTLIGHTS = 5;

/*
* if Uv is bigger than 1.0, it will automatically tile
* if Uv is less than 1.0, it will stretch to fit entire face
* if Uv is 0, it wipes out everything
* (Uv setting to 2.0 gave four tiles (2x2))
*/
struct Vertex {
	glm::vec3 Position{ 0.f, 0.f, 0.f };
	glm::vec3 Color{ 0.8, 0.2, 0.3 };
	glm::vec3 Normal{ 0.0f, 0.0f, 0.0f };
	glm::vec2 Uv{ 1.0f, 1.0f }; // default values
};


struct DirectionalLight {
	glm::vec3 Direction{};

	glm::vec3 AmbientColor{};
	glm::vec3 DiffuseColor{};
	glm::vec3 SpecColor{};

};

struct PointLightStruct {
	glm::vec3 Position{};

	glm::vec3 AmbientColor{};
	glm::vec3 DiffuseColor{};
	glm::vec3 SpecColor{};

	float ConstantVar{ 1.f };
	float LinearVar{ 0.f };
	float QuadVar{ 0.f };


};


struct SceneParameters {
	glm::mat4 ProjectionMatrix{ 1.f };
	glm::mat4 ViewMatrix{ 1.f };

	//uint32_t LightsInScene{ 0 };
	//glm::vec3 LightPos0{};
	//glm::vec3 LightPos1{};

	// var for specular lighting
	glm::vec3 CamPosition{};


	/// <summary>
	/// hardcoded in app.cpp for now
	/// </summary>
	DirectionalLight DirLight{};

//	std::vector<glm::vec3> Lights{};
	std::vector<PointLightStruct> Lights{};

};


struct PredefinedShapes {

	// for passing norm vars between objects and shader
	static inline void UpdateNorms(Vertex& p1, Vertex& p2, Vertex& p3) {
		glm::vec3 U = p2.Position - p1.Position;
		glm::vec3 V = p3.Position - p1.Position;
		
		auto normal = glm::cross(U, V);

		p1.Normal = normal;
		p2.Normal = normal;
		p3.Normal = normal;

	}

	//////////////////////////////////  Cylinder ////////////////////////////////////////
	//// cylinder code inspired and modified from songho.ca:						/////
	////	https://www.songho.ca/opengl/gl_cylinder.html							/////
	/////////////////////////////////////////////////////////////////////////////////////
	static inline std::vector<Vertex> getUnitCircleVerticesAlt(uint32_t sectorCount) {
		const float PI = 3.1415926f;
		float sectorStep = 2 * PI / sectorCount;
		float sectorAngle;

		std::vector<Vertex> vertices{};
		for (auto i = 0; i <= sectorCount; i++) {
			sectorAngle = static_cast<float>(i) * sectorStep;
			vertices.push_back({
				// position
				{
					std::cos(sectorAngle),
					std::sin(sectorAngle),
					0
				}
				});
		}

		return vertices;
	}

	static inline std::tuple<std::vector<Vertex>, std::vector<uint32_t>> BuildCylinderSmooth(uint32_t sectorCount, float baseRadius, float height) {
		std::vector<Vertex> vertices{};
		std::vector<uint32_t> indices{};

		auto unitVertices = getUnitCircleVerticesAlt(sectorCount);

		// put side vertices to arrays, and build the sides
		for (int i = 0; i < 2; ++i)
		{
			float h = -height / 2.0f + static_cast<float>(i) * height; // z value; -h/2 to h/2
			float t = 1.0f - i;		// vertical tex coord; 1 to 0

			uint32_t vertexIndex{ 0 };
			for (auto vertex : unitVertices) {
				vertices.push_back({
					{
						// position (changed x and y, to spin cylinder)
						vertex.Position.x * baseRadius,
						vertex.Position.y * baseRadius,
						h
					},
					{
						////color
						//vertexIndex % 3 == 0 ? 1.f : 0.f,
						//vertexIndex % 3 == 1 ? 1.f : 0.f,
						//vertexIndex % 3 == 2 ? 1.f : 0.f,
						1.f, 1.f, 0.f,
					},
					{
						//norm
						vertex.Position.x = baseRadius,
						vertex.Position.y = baseRadius,
						vertex.Position.z * baseRadius,
					},
					{
						// uv
						// multiply by 2, 3, 4, etc... to increase tex tiles
						(static_cast<float>(vertexIndex) / static_cast<float>(sectorCount)) * 4,

						// multiply by 2, 3, 4 etc., to move the tiles
						// multiply by negative to flip the tile horizontally
						t
					},

					});

				vertexIndex++;
			}

		}

		auto baseCenterIndex = vertices.size();
		auto topCenterIndex = baseCenterIndex + sectorCount + 2;

		// build top and bottom
		for (auto i = 0; i < 2; i++) {
			float h = -height / 2.f + static_cast<float>(i) * height;
			float nz = -1.f + static_cast<float>(i) * 2;

			vertices.push_back({
				{0,0,h},
				{1.f, 1.f, 1.f},
				{0,0,nz},
				{0.5f, 0.5f}
				});


			// loop over all unit circle vertices
			uint32_t vertexIndex{ 0 };
			for (auto vertex : unitVertices) {
				vertices.push_back({
					// position
					{
						// change x, y, and you will spin the unit
						vertex.Position.x * baseRadius,
						vertex.Position.y * baseRadius,
						h,
					},
					// color
					{
						/*vertexIndex % 3 == 0 ? 1.f : 0.f,
						vertexIndex % 3 == 1 ? 1.f : 0.f,
						vertexIndex % 3 == 2 ? 1.f : 0.f,*/
						1.0f, 1.0f, 0.0f,
					},
					// normal
					{
						0,
						0,
						nz,
					},
					// Uv
					{
						// change x, y to turn tex 90-degree
						// change middle variable to positive/negative to flip tex 180-degree
						-vertex.Position.x * -0.5f + 0.5f,
						-vertex.Position.y * -0.5f + 0.5f
					}

					});

				vertexIndex++;

			}

		}


		// for side surface
		uint32_t k1 = 0;
		uint32_t k2 = sectorCount + 1;
		for (auto i = 0; i < sectorCount; i++, k1++, k2++) {

			// 2 triangles per sector
			indices.push_back(k1);
			indices.push_back(k1 + 1);
			indices.push_back(k2);

			indices.push_back(k2);
			indices.push_back(k1 + 1);
			indices.push_back(k2 + 1);
		}


		// for bottom surface
		for (uint32_t i = 0, k = baseCenterIndex + 1; i < sectorCount; i++, k++) {
			if (i < sectorCount - 1) {
				indices.push_back(baseCenterIndex);
				indices.push_back(k + 1);
				indices.push_back(k);
			}
			else {
				indices.push_back(baseCenterIndex);
				indices.push_back(baseCenterIndex + 1);
				indices.push_back(k);

			}
		}

		// for top surface
		for (uint32_t i = 0, k = topCenterIndex + 1; i < sectorCount; i++, k++) {
			if (i < sectorCount - 1) {
				indices.push_back(topCenterIndex);
				indices.push_back(k);
				indices.push_back(k + 1);
			}
			else {
				indices.push_back(topCenterIndex);
				indices.push_back(k);
				indices.push_back(topCenterIndex + 1);

			}
		}

		return { vertices, indices };
	}

	/////////////////////////////////////////   Plane ////////////////////////////////////////
// data for the plane
	static inline std::vector<Vertex> planeVertices{

		
		//// bottom face
		//{
		//	{0.5f, -0.5f, 0.5f},
		//	{0.0f, 0.5f, 0.5f },
		//	{},
		//	{0.f, 1.f}
		//},
		//{
		//	{0.5f, -0.5f, -0.5f},
		//	{1.0f, 0.1f, 0.1f },
		//	{},
		//	{0.f, 0.f}
		//},
		//{
		//	{-0.5f, -0.5f, -0.5f},
		//	{0.0f, 0.3f, 0.3f },
		//	{},
		//	{1.0f, 0.0f}
		//},
		//{
		//	{-0.5f, -0.5f, 0.5f},
		//	{0.3f, 0.3f, 0.1f },
		//	{},
		//	{1.f, 1.f}
		//},

		//// bottom tri 1
		//{
		//	{-5.5f, 0.f, -5.5f},
		//	{1.0f, 0.5f, 0.68f },
		//	{},
		//	{0.0f, 1.0f}
		//},
		//{
		//	{ -5.5f, 0.f, 5.5f},
		//	{1.0f, 0.5f, 0.68f },
		//	{},
		//	{1.0f, 0.0f}
		//},
		//{
		//	{ 5.5f, 0.f, 5.5f},
		//	{1.0f, 0.5f, 0.68f },
		//	{},
		//	{1.0f, 1.0f}
		//},

		//// bottom tri 2
		//{
		//	{ 5.5f, 0.f, 5.5f},
		//	{1.0f, 0.5f, 0.68f },
		//	{},
		//	{1.0f, 0.0f}
		//},
		//{
		//	{ 5.5f, 0.f, -5.5f},
		//	{1.0f, 0.5f, 0.68f },
		//	{},
		//	{0.0f, 1.0f}
		//},
		//{
		//	{ -5.5f, 0.f, -5.5f},
		//	{1.0f, 0.5f, 0.68f },
		//	{},
		//	{1.0f, 1.0f}
		//},

		// top face
		{
			{-5.5f, 0.0f, -5.5f},
			{0.0f, 0.1f, 0.8f },
			{},
			{0.f, 1.f}
		},
		{
			{-5.5f, 0.0f, 5.5f},
			{0.3f, 0.1f, 0.8f },
			{},
			{0.f, 0.f}
		},
		{
			{5.5f, 0.0f, 5.5f},
			{0.0f, 0.4f, 0.1f },
			{},
			{1.0f, 0.0f}
		},
		{
			{5.5f, 0.0f, -5.5f},
			{0.1f, 0.5f, 0.0f },
			{},
			{1.f, 1.f}
		},

		// bottom face
		{
			{5.5f, 0.0f, 5.5f},
			{0.0f, 0.5f, 0.5f },
			{},
			{0.f, 1.f}
		},
		{
			{5.5f, 0.0f, -5.5f},
			{1.0f, 0.1f, 0.1f },
			{},
			{0.f, 0.f}
		},
		{
			{-5.5f, 0.0f, -5.5f},
			{0.0f, 0.3f, 0.3f },
			{},
			{1.0f, 0.0f}
		},
		{
			{-5.5f, 0.0f, 5.5f},
			{0.3f, 0.3f, 0.1f },
			{},
			{1.f, 1.f}
		},

	};

	static inline std::vector<uint32_t> planeElements{
	//	2,1,0,
	//	5,4,3,
		0,1,3,
		1,2,3,
		4,7,5,
		7,6,5,
//		6,7,9,
//		7,8,9,

	};

	////////////////////////////////////////////
	// data for the pyramid
	// define the vertices of each triangle
	// base of pyramid is made up of two triangles
	// norm data can be automated via class instead of handcoded manually for each vert
	static inline std::vector<Vertex> pyramidVertices{

		// base - triangle 1
		{
			{-0.5f, 0.f, -0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.0f, -1.f, 0.0f},
			{0.0f, 0.0f}
		},
		{
			{-0.5f, 0.f, 0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.0f, -1.f, 0.0f},
			{1.0f, 0.0f}
		},
		{
			{0.5f, 0.f, 0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.0f, -1.f, 0.0f},
			{0.5f, 1.0f}		// top middle texture point
		},


		// base - triangle 2
		{
			{0.5f, 0.0f, 0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.0f, -1.f, 0.0f},
			{0.0f, 0.0f}
		},
		{
			{0.5f, 0.0f, -0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.0f, -1.f, 0.0f},
			{1.0f, 0.0f}
		},
		{
			{-0.5f, 0.0f, -0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.0f, -1.f, 0.0f},
			{0.5f, 1.0f}		// top middle texture point
		},

		// left back side
		{
			{-0.5f, 0.0f, -0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{-1.f, 0.5f, 0.f},
			{0.0f, 0.0f}
		},
		{
			{-0.5f, 0.0f, 0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{-1.f, 0.5f, 0.f},
			{1.0f, 0.0f}		
		},
		{
			{0.0f, 1.0f, 0.0f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{-1.f, 0.5f, 0.f},
			{0.5f, 1.0f}		},

		// back right
		{
			{-0.5f, 0.0f, -0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.f, 0.5f, -1.f},
			{0.0f, 0.0f}
		},
		{
			{0.5f, 0.0f, -0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.f, 0.5f, -1.f},
			{1.0f, 0.0f}
		},
		{
			{0.0f, 1.0f, 0.0f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{0.f, 0.5f, -1.f},
			{0.5f, 1.0f}
		},

		// right side
		{
			{0.5f, 0.0f, 0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{1.f, 0.5f, 0.f},
			{0.f, 0.f}
		},
		{
			{0.5f, 0.0f, -0.5f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{1.f, 0.5f, 0.f},
			{1.f, 0.f}
		},
		{
			{0.0f, 1.0f, 0.0f},
			{0.6f, 0.f, 0.8f},
			{},
			//			{1.f, 0.5f, 0.f},
			{0.5f, 1.0f}

		},

		// front side
		{
			{-0.5f, 0.0f, 0.5f},
			{0.6f, 0.0f, 0.8f},
			{},
		//	{0.0f, -1.f, 0.0f},
			{0.0f, 0.0f}		// bottom left texture corner
		},
		{
			{0.5f, 0.0f, 0.5f},
			{0.6f, 0.0f, 0.8f},	
			{},
			//	{0.0f, -1.f, 0.0f},
			{1.0f, 0.0f}		// bottom right texture corner
		},
		{
			{0.0f, 1.0f, 0.0f},
			{0.6f, 0.0f, 0.8f},
			{},
			//	{0.0f, -1.f, 0.0f},
			{0.5f, 1.0f}		// top middle texture point
		},


	};

	// assign vertices		 
	//static inline std::vector<uint32_t> pyramidElements{
	//	0, 1, 2,
	//	3, 4, 5,
	//	6, 7, 8,
	//	9, 10, 11,
	//	12,13,14,
	//	//1,2,8,
	//	15,16,17,

	//};

	static inline std::vector<uint32_t> pyramidElements{
		2, 1, 0,	// base front triangle
		5, 4, 3,	// base back triangle
		6, 7, 8,	// left side
		11, 10, 9,	// back side
		12, 13, 14,	// right side
		15, 16, 17,	// front side
	};



	////////////////////////////////////////////////////////////////////////
	/////////////////////       cube main	////////////////////////////////
	static inline std::vector<Vertex> cubeVertices{

		// front face
		{
			{-0.5f, 0.5f, 0.5f},
			{1.0f, 1.0f, 1.0f },
			{},
			{0.f, 2.f}
		},
		{
			{-0.5f, -0.5f, 0.5f},
			{1.0f, 1.0f, 1.0f },
			{},
			{0.f, 0.f}
		},
		{
			{0.5f, -0.5f, 0.5f},
			{1.0f, 1.0f, 1.0f },
			{},
			{2.0f, 0.0f}
		},
		{
			{0.5f, 0.5f, 0.5f},
			{1.0f, 1.0f, 1.0f },
			{},
			{2.f, 2.f}
		},

		// right side
		{
			{0.5f, 0.5f, 0.5f},
			{0.0f, 0.5f, 0.1f },
			{},
			{0.f, 1.f}
		},
		{
			{0.5f, -0.5f, 0.5f},
			{0.0f, 0.5f, 0.1f },
			{},
			{0.f, 0.f}
		},
		{
			{0.5f, -0.5f, -0.5f},
			{0.0f, 0.5f, 0.1f },
			{},
			{1.0f, 0.0f}
		},
		{
			{0.5f, 0.5f, -0.5f},
			{1.0f, 0.5f, 0.1f },
			{},
			{1.f, 1.f}
		},

		// back face
		{
			{0.5f, 0.5f, -0.5f},
			{0.0f, 0.1f, 0.1f },
			{},
			{0.f, 1.f}
		},
		{
			{0.5f, -0.5f, -0.5f},
			{1.0f, 0.0f, 0.3f },
			{},
			{0.f, 0.f}
		},
		{
			{-0.5f, -0.5f, -0.5f},
			{1.0f, 1.0f, 0.1f },
			{},
			{1.0f, 0.0f}
		},
		{
			{-0.5f, 0.5f, -0.5f},
			{0.0f, 0.1f, 0.1f },
			{},
			{1.f, 1.f}
		},

		// left face
		{
			{-0.5f, 0.5f, -0.5f},
			{1.0f, 1.0f, 0.2f },
			{},
			{0.f, 1.f}
		},
		{
			{-0.5f, -0.5f, -0.5f},
			{0.0f, 0.7f, 0.7f },
			{},
			{0.f, 0.f}
		},
		{
			{-0.5f, -0.5f, 0.5f},
			{1.0f, 0.1f, 0.1f },
			{},
			{1.0f, 0.0f}
		},
		{
			{-0.5f, 0.5f, 0.5f},
			{1.0f, 0.1f, 0.1f },
			{},
			{1.f, 1.f}
		},

		// top face
		{
			{-0.5f, 0.5f, -0.5f},
			{0.0f, 0.1f, 0.8f },
			{},
			{0.f, 1.f}
		},
		{
			{-0.5f, 0.5f, 0.5f},
			{0.3f, 0.1f, 0.8f },
			{},
			{0.f, 0.f}
		},
		{
			{0.5f, 0.5f, 0.5f},
			{0.0f, 0.4f, 0.1f },
			{},
			{1.0f, 0.0f}
		},
		{
			{0.5f, 0.5f, -0.5f},
			{0.1f, 0.5f, 0.0f },
			{},
			{1.f, 1.f}
		},

		// bottom face
		{
			{0.5f, -0.5f, 0.5f},
			{0.0f, 0.5f, 0.5f },
			{},
			{0.f, 1.f}
		},
		{
			{0.5f, -0.5f, -0.5f},
			{1.0f, 0.1f, 0.1f },
			{},
			{0.f, 0.f}
		},
		{
			{-0.5f, -0.5f, -0.5f},
			{0.0f, 0.3f, 0.3f },
			{},
			{1.0f, 0.0f}
		},
		{
			{-0.5f, -0.5f, 0.5f},
			{0.3f, 0.3f, 0.1f },
			{},
			{1.f, 1.f}
		},

	};

	static inline std::vector<uint32_t> cubeElements{
		0, 1, 3, 1, 2, 3,	// front face
		4, 5, 7, 5, 6, 7,	// right face
		8, 9, 11, 9, 10, 11, // back face
		12, 13, 15, 13, 14, 15, // left face
		16, 17, 19, 17, 18, 19, // top face
		20, 23, 21, 23, 22, 21, // bottom face
	};

	/////////////////////////////////////////   small box ////////////////////////////////////////
// data for small box
	static inline std::vector<Vertex> smallBoxVertices{

		// front face
		{
			{-0.5f, -0.2f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 2.0f}
		},
		{
			{-0.5f, -0.5f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 0.0f}
		},
		{
			{0.5f, -0.5f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 0.0f}
		},
		{
			{0.5f, -0.2f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 2.0f}
		},

		// right side
		{
			{0.5f, -0.2f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 2.0f}
		},
		{
			{0.5f, -0.5f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 0.0f}
		},
		{
			{0.5f, -0.5f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 0.0f}
		},
		{
			{0.5f, -0.2f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 2.0f}
		},

		// back face
		{
			{0.5f, -0.2f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 2.0f}
		},
		{
			{0.5f, -0.5f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 0.0f}
		},
		{
			{-0.5f, -0.5f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 0.0f}
		},
		{
			{-0.5f, -0.2f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 2.0f}
		},

		// left face
		{
			{-0.5f, -0.2f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 2.0f}
		},
		{
			{-0.5f, -0.5f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 0.0f}
		},
		{
			{-0.5f, -0.5f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 0.0f}
		},
		{
			{-0.5f, -0.2f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 2.0f}
		},

		// top face
		{
			{-0.5f, -0.2f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 2.0f}
		},
		{
			{-0.5f, -0.2f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 0.0f}
		},
		{
			{0.5f, -0.2f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 0.0f}
		},
		{
			{0.5f, -0.2f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 2.0f}
		},

		// bottom face
		{
			{0.5f, -0.5f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 2.0f}
		},
		{
			{0.5f, -0.5f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{0.0f, 0.0f}
		},
		{
			{-0.5f, -0.5f, -0.5f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 0.0f}
		},
		{
			{-0.5f, -0.5f, 0.0f},
			{1.0f, 0.5f, 0.68f },
			{},
			{2.0f, 2.0f}
		},

		//		old color values
		//		{ 1.0f, 0.5f, 0.21f },

	};

	static inline std::vector<uint32_t> smallBoxElements {

		0, 1, 3, 1, 2, 3,	// front face
		4, 5, 7, 5, 6, 7,	// right face
		8, 9, 11, 9, 10, 11, // back face
		12, 13, 15, 13, 14, 15, // left face
		16, 17, 19, 17, 18, 19, // top face
		20, 23, 21, 23, 22, 21, // bottom face

	};

};

