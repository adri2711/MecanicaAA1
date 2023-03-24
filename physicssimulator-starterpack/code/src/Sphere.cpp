#include "Sphere.h"

#include <glm/detail/func_geometric.hpp>

Sphere::Sphere(glm::vec3 coordinates, float radius) : _coordinates(coordinates), _radius(radius), Collider(true, SPHERE)
{
}

Sphere::~Sphere()
{
}

float Sphere::CalculateA(glm::vec3 currentPosition)
{
    return glm::dot(currentPosition - _coordinates, currentPosition - _coordinates);
}

float Sphere::CalculateB(glm::vec3 currentPosition, glm::vec3 vectorBetweenPositions)
{
    return 2 * ((currentPosition.x - _coordinates.x) * vectorBetweenPositions.x) +
        2 * ((currentPosition.y - _coordinates.y) * vectorBetweenPositions.y) +
        2 * ((currentPosition.z - _coordinates.z) * vectorBetweenPositions.z);
}

float Sphere::CalculateC(glm::vec3 vectorBetweenPositions)
{
    return glm::dot(vectorBetweenPositions, vectorBetweenPositions);
}
