#include "EulerFrame.h"

EulerFrame::EulerFrame()
{
}

EulerFrame::EulerFrame(glm::vec3 currentPosition) : _position(currentPosition)
{
    _velocity = glm::vec3(0,0,0);
}

EulerFrame::~EulerFrame()
{
}

glm::vec3 EulerFrame::CalculateNextPosition(float dt)
{
    return _position = Solver::EulerSolverPosition(_position, _velocity, dt);
}

glm::vec3 EulerFrame::CalculateNextVelocity(glm::vec3 force, float dt)
{
    return _velocity = Solver::EulerSolverVelocity(_velocity, force, dt);    
}
