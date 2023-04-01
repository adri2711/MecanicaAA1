#include "VerletFrame.h"

VerletFrame::VerletFrame()
{}

VerletFrame::VerletFrame(glm::vec3 lastPosition, glm::vec3 currentPosition) : _lastPosition(glm::vec3(lastPosition)), _currentPosition(currentPosition)
{
	_nextPosition = currentPosition;
}

VerletFrame::~VerletFrame()
{
}

glm::vec3 VerletFrame::CalculateNextPosition(glm::vec3 position, glm::vec3 acceleration, float dt)
{
	_lastPosition = _currentPosition;
	_currentPosition = _nextPosition;
	return _nextPosition = Solver::VerletSolverPosition(position, _lastPosition, acceleration, dt);
}

glm::vec3 VerletFrame::CalculateNextVelocity(float dt)
{
	return Solver::VerletSolverVelocity(_currentPosition, _nextPosition , dt);
}

void VerletFrame::SetNextPosition(glm::vec3 nextPosition)
{
	_nextPosition = nextPosition;
}



