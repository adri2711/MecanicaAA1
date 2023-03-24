#pragma once
#include "Collider.h"

class Capsule : public Collider
{
private:


public:
    
    glm::vec3 _pointACoordinates;
    glm::vec3 _pointBCoordinates;    
    float _radius;

    Capsule(glm::vec3 pointACoordinates, glm::vec3 pointBCoordinates, float radius);
    ~Capsule();
};
