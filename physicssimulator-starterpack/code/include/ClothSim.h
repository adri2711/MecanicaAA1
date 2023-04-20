#pragma once
#include "Simulator.h"
#include "PrimitiveManager.h"
#include <imgui/imgui.h>

#include "ColliderSystem.h"
#include "MeshSystem.h"
#include <ctime>
#include <conio.h>

#define DT_DIVISOR 10.f

extern graphics::PrimitiveManager manager;

class ClothSim : public Simulator{

private:

	float _initialTime = 20.0f;
	float _currentTime = _initialTime;
	
	MeshSystem* _meshSystem;
	ColliderSystem* _colliderSystem;

public:

	ClothSim();
	~ClothSim();

	// Inherited via Simulator
	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
};

