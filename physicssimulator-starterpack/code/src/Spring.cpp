#include "Spring.h"

Spring::Spring(SpringType springType, float elasticity, float damping, float originalLength)
    : _springType(springType), _elasticity(elasticity), _damping(damping), _originalLength(originalLength)
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