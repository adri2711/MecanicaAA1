#include "Capsule.h"

Capsule::Capsule(glm::vec3 pointACoordinates, glm::vec3 pointBCoordinates, float radius) :
    _pointACoordinates(pointACoordinates), _pointBCoordinates(pointBCoordinates), Collider(true, CAPSULE)
{
}

Capsule::~Capsule()
{
}

glm::vec3 Capsule::GetPointACoordinates()
{
    return _pointACoordinates;
}

glm::vec3 Capsule::GetPointBCoordinates()
{
    return _pointBCoordinates;    
}

float Capsule::GetRadius()
{
    return _radius;
}
