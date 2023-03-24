#pragma once
#include "Collider.h"

class Capsule : public Collider
{
private:

    glm::vec3 _pointACoordinates;
    glm::vec3 _pointBCoordinates;    
    float _radius;

public:

    Capsule(glm::vec3 pointACoordinates, glm::vec3 pointBCoordinates, float radius);
    ~Capsule();

    glm::vec3 GetPointACoordinates();
    glm::vec3 GetPointBCoordinates();
    float GetRadius();
};
