#pragma once

#include "Solver.h"

class EulerFrame
{

private:
		
    glm::vec3 _position;
    glm::vec3 _velocity;

public:

    EulerFrame();
    EulerFrame(glm::vec3 currentPosition);
    ~EulerFrame();

    /*void SetLastPosition(glm::vec3 lastPosition);
    glm::vec3 GetLastPosition();

    void SetCurrentPosition(glm::vec3 currentPosition);
    glm::vec3 GetCurrentPosition();

    void SetNextPosition(glm::vec3 nextPosition);
    glm::vec3 GetNextPosition();*/

    glm::vec3 CalculateNextPosition(float dt);
    glm::vec3 CalculateNextVelocity(glm::vec3 force, float dt);

};
