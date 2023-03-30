#pragma once
#include <glm/glm.hpp>

static class Solver
{
public:

	static glm::vec3 VerletSolverPosition(glm::vec3 currentPosition, glm::vec3 lastPosition, float dt);
	static glm::vec3 VerletSolverVelocity(glm::vec3 currentPosition, glm::vec3 nextPosition, float dt);
	static glm::vec3 EulerSolver();
};