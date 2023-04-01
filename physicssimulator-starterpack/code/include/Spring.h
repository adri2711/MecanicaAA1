#pragma once
#include "VerletFrame.h"

enum class SpringType {STRUCTURAL, SHEAR, BEND};

class Spring
{
private:
    
    int _connectPointIndex;
    glm::vec3** _connectedMeshNodePosition;
    SpringType _springType;
    float _elasticity;
    float _damping;
    float _originalLength;
    float _force;
    
public:

    //Spring(SpringType springType, float elasticity, float damping, float originalLength);
    Spring(SpringType springType, float elasticity, float damping, float originalLength, int connectPointIndex, glm::vec3** connectedMeshNodePosition);
    ~Spring();

    void Visit();
    
    SpringType GetSpringType();
    float GetElasticity();
    float GetDamping();
    float GetOriginalLength();
    int GetConnectionPoint();
    float CalculateForce(glm::vec3 meshNodePosition);
    
};
