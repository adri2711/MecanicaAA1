#pragma once
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
};