#include "VerletFrame.h"

VerletFrame::VerletFrame()
{}

VerletFrame::VerletFrame(glm::vec3 lastPosition, glm::vec3 currentPosition) : _lastPosition(lastPosition), _currentPosition(currentPosition)
{
	_nextPosition = currentPosition;
}

VerletFrame::~VerletFrame()
{
}

glm::vec3 VerletFrame::CalculateNextPosition(float dt)
{
	_lastPosition = _currentPosition;
	_currentPosition = _nextPosition;
	_nextPosition = Solver::VerletSolverPosition(_currentPosition, _lastPosition, dt);
	return _nextPosition;
}

glm::vec3 VerletFrame::CalculateNextVelocity(float dt)
{
	return Solver::VerletSolverVelocity(_currentPosition, _nextPosition , dt);
}
