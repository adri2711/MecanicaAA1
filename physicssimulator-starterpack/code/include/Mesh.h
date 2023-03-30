#pragma once
#include "Simulator.h"
#include "PrimitiveManager.h"
#include "Solver.h"

#define MIN_WIDTH_LENGTH 14
#define MAX_WIDTH_LENGTH 20

#define MIN_HEIGHT_LENGTH 18
#define MAX_HEIGHT_LENGTH 24

#define MIN_DISTANCE_BETWEEN_PARTICLES 0.4f
#define MAX_DISTANCE_BETWEEN_PARTICLES 0.6f

class Mesh
{

private:

	std::vector<glm::vec3> _positions;
	glm::vec3 _startPosition;
	float _distanceBetweenParticles;

public: 


	Mesh(glm::vec3 startPosition, float distanceBetweenParticles);
	~Mesh();	

	const float* GetFirstPosition();
	void UpdatePosition(float dt);
};

