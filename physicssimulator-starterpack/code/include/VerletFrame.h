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

	/*void SetLastPosition(glm::vec3 lastPosition);
	glm::vec3 GetLastPosition();

	void SetCurrentPosition(glm::vec3 currentPosition);
	glm::vec3 GetCurrentPosition();

	void SetNextPosition(glm::vec3 nextPosition);
	glm::vec3 GetNextPosition();*/

	glm::vec3* CalculateNextPosition(float dt);
	glm::vec3 CalculateNextVelocity(float dt);

};

