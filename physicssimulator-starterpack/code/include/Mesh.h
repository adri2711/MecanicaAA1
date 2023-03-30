#pragma once

#include <vector>
#include "VerletFrame.h"
#include "../MeshNode.h"

#define WIDTH 14
#define HEIGHT 18

#define MIN_DISTANCE_BETWEEN_PARTICLES 0.4f
#define MAX_DISTANCE_BETWEEN_PARTICLES 0.6f

#define MIN_STRUCTURAL_CONSTANT 0.1f
#define MAX_STRUCTURAL_CONSTANT 10.0f

#define MIN_SHEAR_CONSTANT 0.1f
#define MAX_SHEAR_CONSTANT 10.0f

#define MIN_BEND_CONSTANT 0.1f
#define MAX_BEND_CONSTANT 10.0f

class Mesh
{

private:

	std::vector<MeshNode> _meshNodes;
	std::vector<glm::vec3> _positions;
	glm::vec3 _startPosition;

public: 

	float _distanceBetweenParticles;
	float _structuralElasticity;
	float _shearElasticity;
	float _bendElasticity;
	float _damping;

	Mesh(glm::vec3 startPosition, float distanceBetweenParticles, float structuralElasticity, float shearElasticity, float bendElasticity, float damping);
	~Mesh();

	void ConnectNodesWithSprings();

	const float* GetFirstPosition();
	void UpdateNodesPositions(float dt);
};

