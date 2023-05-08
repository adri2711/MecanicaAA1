#pragma once
#include <ctime>
#include <conio.h>
#include "Simulator.h"
#include "RigidBodySystem.h"
#include "ColliderSystem.h"

#define DT_DIVISOR 1.f

class RigidBodySim : public Simulator
{
private:

    float _initialTime = 15.0f;
    float _currentTime = _initialTime;

    RigidBodySystem* _rigidBodySystem;
    ColliderSystem* _colliderSystem;

    bool _reset;

public:

    RigidBodySim();
    ~RigidBodySim() override;

    // Inherited via Simulator
    void Update(float dt) override;
    void RenderUpdate() override;
    void RenderGui() override;
};