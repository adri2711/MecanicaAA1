#pragma once

enum class SpringType {STRUCTURAL, SHEAR, BEND};

class Spring
{
private:

    SpringType _springType;
    float _elasticity;
    float _damping;
    float _originalLength;
    
public:

    Spring(SpringType springType, float elasticity, float damping, float originalLength);
    ~Spring();

    SpringType GetSpringType();
    float GetElasticity();
    float GetDamping();
    float GetOriginalLength();
};
