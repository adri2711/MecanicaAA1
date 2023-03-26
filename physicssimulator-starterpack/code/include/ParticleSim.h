#pragma once
#include <Simulator.h>

#include "ColliderSystem.h"
#include "ParticleSystem.h"

class ParticleSim : public Simulator {
public:
	ParticleSim();
	~ParticleSim();

	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
	

private:
	std::vector<ParticleSystem*> particleSystems;
	ColliderSystem _colliderSystem;
};