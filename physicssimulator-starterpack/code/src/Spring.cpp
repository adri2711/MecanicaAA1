#include "Spring.h"

Spring::Spring(SpringType springType, float rigidity, float damping, float originalLength, int connectPointIndex,
    glm::vec3* connectedMeshNodePosition, glm::vec3* connectedMeshNodeVelocity, glm::vec3* connectedMeshNodeForce)
    : _connectPointIndex(connectPointIndex), _connectedMeshNodePosition(connectedMeshNodePosition), _connectedMeshNodeVelocity(connectedMeshNodeVelocity),
    _connectedMeshNodeForce(connectedMeshNodeForce), _springType(springType), _rigidity(rigidity),
    _damping(damping), _originalLength(originalLength)
{ 
}

Spring::~Spring()
{    
}

glm::vec3* Spring::GetConnectedMeshPosition()
{
    return _connectedMeshNodePosition;
}

int Spring::GetConnectionPointIndex()
{
    return _connectPointIndex;
}

glm::vec3 Spring::CalculateForce(glm::vec3 initialMeshNodePosition, glm::vec3 initialMeshNodeVelocity)
{
    float distanceStretched = glm::length(initialMeshNodePosition - *_connectedMeshNodePosition) - _originalLength;

    glm::vec3 vectorNormalized = (initialMeshNodePosition - *_connectedMeshNodePosition) / glm::length(initialMeshNodePosition - *_connectedMeshNodePosition);
    float dampingTerm = _damping * glm::dot((initialMeshNodeVelocity - *_connectedMeshNodeVelocity), vectorNormalized);

    glm::vec3 forceApplied = -(_rigidity * distanceStretched + dampingTerm) * vectorNormalized; 

    *_connectedMeshNodeForce += -forceApplied;
    
    return forceApplied; 
}