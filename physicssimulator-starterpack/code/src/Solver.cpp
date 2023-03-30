#include "Solver.h"


glm::vec3 Solver::VerletSolverPosition(glm::vec3 currentPosition, glm::vec3 lastPosition, float dt)
{
	return currentPosition + (currentPosition - lastPosition) + glm::vec3(0.0f, -9.81f, 0.0f) * pow(dt, 2.f);
}

glm::vec3 Solver::VerletSolverVelocity(glm::vec3 currentPosition, glm::vec3 nextPosition, float dt)
{
	return (nextPosition - currentPosition) / dt;
}
