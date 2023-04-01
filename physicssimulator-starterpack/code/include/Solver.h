#pragma once
#include <glm/glm.hpp>

class Solver
{
	
	
public:

	static glm::vec3 VerletSolverPosition(glm::vec3 currentPosition, glm::vec3 lastPosition, glm::vec3 acceleration, float dt);
	static glm::vec3 VerletSolverVelocity(glm::vec3 currentPosition, glm::vec3 nextPosition, float dt);
	static glm::vec3 EulerSolverPosition(glm::vec3 currentPosition, glm::vec3 currentVelocity, float dt);
	static glm::vec3 EulerSolverVelocity(glm::vec3 currentVelocity, glm::vec3 acceleration, float dt);
};