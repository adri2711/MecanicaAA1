#pragma once
#include "ParticleSystem.h"

class ParticleSim : public Simulator {
public:
	ParticleSim();
	~ParticleSim();

	void Update(float dt) override;

private:
	ParticleSystem particleSystem;
};