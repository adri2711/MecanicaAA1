#pragma once
#include "ParticleSystem.h"
class FountainParticleSystem : public ParticleSystem
{
protected:
	virtual void ParticleUpdate(int i, float dt) override;
	virtual Particle CreateParticle() override;
	glm::vec3 dirNormalised = glm::vec3(0.f, 0.f, 0.f);
public:
	glm::vec3 coneDir = glm::vec3(0.f, 1.f, 0.f);
	float angle = 45.f; 
	float velocityMagnitude = 1.f;
	virtual void Setup() override;
};

