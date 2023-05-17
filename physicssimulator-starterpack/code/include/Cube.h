#pragma once
#include "RigidBody.h"

class Cube : public RigidBody
{

private:
    graphics::CubePrimitive* _cube;

    std::vector<graphics::SpherePrimitive*> _spheresPrimitive;

    std::vector<Sphere> _spheres;

    glm::mat3 CalculateIBody();   
    
public:

    Cube(float initialRotation, glm::vec3 initialDirection, glm::vec3 centerOfMass, glm::vec3 scale, float mass,
        glm::vec3 linearVelocity, glm::vec3 angularVelocity, std::vector<glm::vec3> particlesLocalPosition);
    ~Cube() override;
    void Update(float dt) override;
    
};
