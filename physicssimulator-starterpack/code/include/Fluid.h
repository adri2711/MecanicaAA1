#pragma once

#include <vector>

#include "ColliderSystem.h"
#include "../FluidNode.h"
#include "../Wave.h"

#define WIDTH 15
#define HEIGHT 15
#define MIN_DISTANCE_BETWEEN_PARTICLES .7f
#define MAX_DISTANCE_BETWEEN_PARTICLES 2.f

class Fluid
{

private:

	std::vector<FluidNode> _fluidNodes;
	std::vector<Wave> _waves;
	std::vector<glm::vec3> _positions;
	std::vector<glm::vec3> _previousPositions;
	glm::vec3 _startPosition;

public:

	float distanceBetweenParticles;

	Fluid(glm::vec3 startPosition, float distanceBetweenParticles);
	~Fluid();

	const float* GetFirstPosition();
	void UpdateNodesPositions(std::vector<Collider*> colliders, float dt);
	void AddWave(Wave newWave);

	std::vector<glm::vec3> GetPositions();
};
