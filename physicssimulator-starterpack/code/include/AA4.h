#pragma once
#include "Simulator.h"
#include <PrimitiveManager.h>

extern graphics::PrimitiveManager manager;

class AA4 : public Simulator
{
private:

    graphics::CubePrimitive* _cube;
    glm::mat3 _rotationMatrix;
    glm::mat3 _angularVelocityMatrix;

    glm::vec3 _angularVelocity;

    float roll = 0.f;
    float pitch = 0.f;
    float yaw = 0.f;

public:

    AA4();
    ~AA4();

    // Inherited via Simulator
    void Update(float dt) override;
    void RenderUpdate() override;
    void RenderGui() override;
};