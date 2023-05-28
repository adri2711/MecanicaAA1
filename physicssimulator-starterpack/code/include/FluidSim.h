#pragma once
#include "Simulator.h"
#include "PrimitiveManager.h"
#include <imgui/imgui.h>

#include "ColliderSystem.h"
#include "FluidSystem.h"
#include <ctime>
#include <conio.h>

#define DT_DIVISOR 20.f

extern graphics::PrimitiveManager manager;

class FluidSim : public Simulator{

private:

	float _initialTime = 20.0f;
	float _currentTime = _initialTime;
	
	FluidSystem* _fluidSystem;
	ColliderSystem* _colliderSystem;

public:

	FluidSim();
	~FluidSim();

	// Inherited via Simulator
	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
};

