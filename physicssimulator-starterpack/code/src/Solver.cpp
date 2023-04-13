#include "Solver.h"

glm::vec3 Solver::VerletSolverPosition(glm::vec3 currentPosition, glm::vec3 lastPosition, glm::vec3 acceleration, float dt)
{	
	return currentPosition + (currentPosition - lastPosition) + (acceleration  + glm::vec3(0.f, -9.81f, 0.f)) * pow(dt, 2.f);
}

glm::vec3 Solver::VerletSolverVelocity(glm::vec3 currentPosition, glm::vec3 nextPosition, float dt)
{
	return (nextPosition - currentPosition) / dt;
}

glm::vec3 Solver::EulerSolverPosition(glm::vec3 currentPosition, glm::vec3 currentVelocity, float dt)
{
	return currentPosition + currentVelocity * dt;
}

glm::vec3 Solver::EulerSolverVelocity(glm::vec3 currentVelocity, glm::vec3 acceleration, float dt)
{
	return currentVelocity + (acceleration + glm::vec3(0.f, -9.81f, 0.f)) * dt;
}
