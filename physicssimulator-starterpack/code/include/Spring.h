#pragma once
#include "VerletFrame.h"

enum class SpringType {STRUCTURAL, SHEAR, BEND};

class Spring
{
private:
    
    int _connectPointIndex;
    glm::vec3** _connectedMeshNodePosition;
    glm::vec3** _connectedMeshNodeVelocity;
    SpringType _springType;
    float _elasticity;
    float _damping;
    float _originalLength;
    
public:

    Spring(SpringType springType, float elasticity, float damping, float originalLength, int connectPointIndex,
        glm::vec3** connectedMeshNodePosition, glm::vec3** connectedMeshNodeVelocity);
    ~Spring();

    glm::vec3** GetConnectedMeshPosition();
    int GetConnectionPoint();
    glm::vec3 CalculateForce(glm::vec3 initialMeshNodePosition, glm::vec3 initialMeshNodeVelocity);
    
};
