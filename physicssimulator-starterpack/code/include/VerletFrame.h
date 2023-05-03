#pragma once

#include "Solver.h"

class VerletFrame
{

private:
		
	glm::vec3 _lastPosition;
	glm::vec3 _currentPosition;
	glm::vec3 _nextPosition;

public:

	VerletFrame();
	VerletFrame(glm::vec3 lastPosition, glm::vec3 currentPosition);
	~VerletFrame();

	glm::vec3 CalculateNextPosition(glm::vec3 position, glm::vec3 acceleration, float dt);
	glm::vec3 CalculateNextVelocity(float dt);

	void SetNextPosition(glm::vec3 nextPosition);

};

