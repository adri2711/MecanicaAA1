#include "Spring.h"

Spring::Spring(SpringType springType, float elasticity, float damping, float originalLength, int connectPointIndex)
    : _springType(springType), _elasticity(elasticity), _damping(damping), _originalLength(originalLength), _connectPointIndex(connectPointIndex)
{}

Spring::~Spring()
{
    
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
