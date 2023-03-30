#pragma once
#include "Simulator.h"
#include "PrimitiveManager.h"

#include "ColliderSystem.h"
#include "ParticleSystem.h"
#include "MeshSystem.h"

extern graphics::PrimitiveManager manager;

class ClothSim : public Simulator{

private:
	
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

