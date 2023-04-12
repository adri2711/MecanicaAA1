#include "Spring.h"

Spring::Spring(SpringType springType, float elasticity, float damping, float originalLength, int connectPointIndex,
    glm::vec3** connectedMeshNodePosition, glm::vec3** connectedMeshNodeVelocity, glm::vec3** connectedMeshNodeAcceleration)
    : _connectPointIndex(connectPointIndex), _connectedMeshNodePosition(connectedMeshNodePosition), _connectedMeshNodeVelocity(connectedMeshNodeVelocity),
    _connectedMeshNodeAcceleration(connectedMeshNodeAcceleration), _springType(springType), _elasticity(elasticity),
    _damping(damping), _originalLength(originalLength)
{ 
}

Spring::~Spring()
{    
}

glm::vec3** Spring::GetConnectedMeshPosition()
{
    return _connectedMeshNodePosition;
}

int Spring::GetConnectionPoint()
{
    return _connectPointIndex;
}

glm::vec3 Spring::CalculateForce(glm::vec3 initialMeshNodePosition, glm::vec3 initialMeshNodeVelocity)
{
    glm::vec3 forceApplied;
    
    float distanceStretched = glm::length(initialMeshNodePosition - **_connectedMeshNodePosition) - _originalLength;

    glm::vec3 vectorNormalized = (initialMeshNodePosition - **_connectedMeshNodePosition) / glm::length(initialMeshNodePosition - **_connectedMeshNodePosition);
    glm::vec3 dampingTerm = _damping * (initialMeshNodePosition - **_connectedMeshNodeVelocity) * vectorNormalized;

    forceApplied = -(_elasticity * distanceStretched + dampingTerm) * vectorNormalized; 

    **_connectedMeshNodeAcceleration += -forceApplied;
    
    return forceApplied; 
}