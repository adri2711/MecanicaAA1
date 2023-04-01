#pragma once
#include "VerletFrame.h"

enum class SpringType {STRUCTURAL, SHEAR, BEND};

class Spring
{
private:
    
    int _connectPointIndex;
    SpringType _springType;
    float _elasticity;
    float _damping;
    float _originalLength;
    
public:

    //Spring(SpringType springType, float elasticity, float damping, float originalLength);
    Spring(SpringType springType, float elasticity, float damping, float originalLength, int connectPointIndex);
    ~Spring();

    SpringType GetSpringType();
    float GetElasticity();
    float GetDamping();
    float GetOriginalLength();
    int GetConnectionPoint();
};
