#pragma once
#include "VerletFrame.h"

enum class SpringType {STRUCTURAL, SHEAR, BEND};

class Spring
{
private:
    
    int _connectPointIndex;
    glm::vec3* _connectedMeshNodePosition;
    glm::vec3* _connectedMeshNodeVelocity;
    glm::vec3* _connectedMeshNodeForce;
    SpringType _springType;
    float _rigidity;
    float _damping;
    float _originalLength;
    
public:

    Spring(SpringType springType, float rigidity, float damping, float originalLength, int connectPointIndex,
        glm::vec3* connectedMeshNodePosition, glm::vec3* connectedMeshNodeVelocity, glm::vec3* connectedMeshNodeForce);
    ~Spring();

    glm::vec3* GetConnectedMeshPosition();
    int GetConnectionPointIndex();
    glm::vec3 CalculateForce(glm::vec3 initialMeshNodePosition, glm::vec3 initialMeshNodeVelocity);
    
};
