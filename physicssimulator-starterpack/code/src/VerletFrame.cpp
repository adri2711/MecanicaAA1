#include "VerletFrame.h"

VerletFrame::VerletFrame(glm::vec3 _lastPosition, glm::vec3 _currentPosition) : _lastPosition(_lastPosition), _currentPosition(_currentPosition)
{
}

VerletFrame::~VerletFrame()
{
}

void VerletFrame::SetLastPosition(glm::vec3 lastPosition)
{
	_lastPosition = lastPosition;
}

glm::vec3 VerletFrame::GetLastPosition()
{
	return _lastPosition;
}

void VerletFrame::SetCurrentPosition(glm::vec3 currentPosition)
{
	_currentPosition = currentPosition;
}

glm::vec3 VerletFrame::GetCurrentPosition()
{
	return _currentPosition;
}

void VerletFrame::SetNextPosition(glm::vec3 nextPosition)
{
	_nextPosition = nextPosition;
}

glm::vec3 VerletFrame::GetNextPosition()
{
	return _nextPosition;
}
