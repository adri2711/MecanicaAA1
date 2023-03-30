#pragma once

#include <glm/glm.hpp>

class VerletFrame
{

private:

	glm::vec3 _lastPosition;
	glm::vec3 _currentPosition;
	glm::vec3 _nextPosition;

public:

	VerletFrame(glm::vec3 _lastPosition, glm::vec3 _currentPosition);
	~VerletFrame();

	void SetLastPosition(glm::vec3 lastPosition);
	glm::vec3 GetLastPosition();

	void SetCurrentPosition(glm::vec3 currentPosition);
	glm::vec3 GetCurrentPosition();

	void SetNextPosition(glm::vec3 nextPosition);
	glm::vec3 GetNextPosition();

};

