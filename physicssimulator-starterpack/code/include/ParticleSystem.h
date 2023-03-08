#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <PrimitiveManager.h>
#include <vector>
#include "Particle.h"


class ParticleSystem : public Object
{
	#define MIN_EMISSION_RATE 100
	#define MAX_EMISSION_RATE 1000

protected:
	graphics::ParticlesPrimitive* particlePrimitives;
	std::vector<Particle> particles;
	glm::vec3* positions;
	float emitTime;

	const glm::vec3 gravity = { 0.f, -9.81f, 0.f };

	glm::vec3 EulerSolver(glm::vec3 x0, glm::vec3 v0, float dt);
	virtual void ParticleUpdate(int i, float dt);
	virtual Particle CreateParticle();
	virtual void DeleteParticle(int i);
	void EmitParticles(int emissionCount);
	void UpdatePrimitive();
public:
	glm::vec3 startVelocity = { 0.f, 0.f, 0.f };
	float emissionRate = 100.f;
	float particleMass = 1.f;
	float particleLifeTime = 5.f;

	ParticleSystem() : Object(glm::vec3(0, 0, 0)) {}
	~ParticleSystem();
	virtual void Setup();
	virtual void Update(float dt);
	virtual void Render();
};

