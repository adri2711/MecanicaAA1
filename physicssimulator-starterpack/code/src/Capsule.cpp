#include "Capsule.h"

Capsule::Capsule(glm::vec3 pointACoordinates, glm::vec3 pointBCoordinates, float radius) :
    _pointACoordinates(pointACoordinates), _pointBCoordinates(pointBCoordinates), _radius(radius), Collider(true, CAPSULE)
{
}

Capsule::~Capsule()
{
    delete this;
}
