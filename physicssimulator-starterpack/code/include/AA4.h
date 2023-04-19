#pragma once
#include "Simulator.h"
#include <PrimitiveManager.h>

extern graphics::PrimitiveManager manager;

class AA4 : public Simulator
{
private:

    graphics::CubePrimitive* _cube;
    glm::mat3 _rotationMatrix;

public:

    AA4();
    ~AA4();

    // Inherited via Simulator
    void Update(float dt) override;
    void RenderUpdate() override;
    void RenderGui() override;
};