#pragma once

#include <vector>

#include "ColliderSystem.h"
#include "../FluidNode.h"
#include "../Wave.h"
#include "BuoyantSphere.h"

#define WIDTH 15
#define HEIGHT 15
#define MIN_DISTANCE_BETWEEN_PARTICLES .7f
#define MAX_DISTANCE_BETWEEN_PARTICLES 2.f

class Fluid
{

private:

	std::vector<FluidNode*> _fluidNodes;
	std::vector<glm::vec3> _positions;
	glm::vec3 _startPosition;
	float t;

public:

	float density;
	std::vector<Wave> _waves;

	float distanceBetweenParticles;

	Fluid(glm::vec3 startPosition, float distanceBetweenParticles, float density);
	~Fluid();

	const float* GetFirstPosition();
	void UpdateNodesPositions(std::vector<Collider*> colliders, float dt);
	void AddWave(Wave newWave);
	float FindSubmergedVolume(const BuoyantSphere &sphere);

	std::vector<glm::vec3> GetPositions();
};
