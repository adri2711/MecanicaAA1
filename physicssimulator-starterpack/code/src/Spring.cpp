#include "Spring.h"

#include <iostream>

Spring::Spring(SpringType springType, float elasticity, float damping, float originalLength, int connectPointIndex, glm::vec3** connectedMeshNodePosition)
    : _connectPointIndex(connectPointIndex), _connectedMeshNodePosition(connectedMeshNodePosition),
    _springType(springType), _elasticity(elasticity), _damping(damping), _originalLength(originalLength)
{ 
}

Spring::~Spring()
{
    
}

void Spring::Visit()
{
    auto aut = 1+1;
}

SpringType Spring::GetSpringType()
{
    return _springType;
}

float Spring::GetElasticity()
{
    return _elasticity;
}

float Spring::GetDamping()
{
    return _damping;
}

float Spring::GetOriginalLength()
{
    return _originalLength;
}

int Spring::GetConnectionPoint()
{
    return _connectPointIndex;
}

float Spring::CalculateForce(glm::vec3 meshNodePosition)
{
    return _force;
}

