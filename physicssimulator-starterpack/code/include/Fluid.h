#pragma once

#include <vector>

#include "ColliderSystem.h"
#include "../FluidNode.h"

#define WIDTH 10
#define HEIGHT 10
#define MIN_DISTANCE_BETWEEN_PARTICLES 0.4f
#define MAX_DISTANCE_BETWEEN_PARTICLES 0.5f

class Fluid
{

private:

	std::vector<FluidNode> _FluidNodes;
	std::vector<glm::vec3> _positions;
	glm::vec3 _startPosition;

public:

	float distanceBetweenParticles;

	Fluid(glm::vec3 startPosition, float distanceBetweenParticles);
	~Fluid();

	const float* GetFirstPosition();
	void UpdateNodesPositions(std::vector<Collider*> colliders, float dt);

	std::vector<glm::vec3> GetPositions();
};
