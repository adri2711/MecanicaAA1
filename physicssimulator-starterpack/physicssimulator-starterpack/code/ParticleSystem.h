#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <ParticleSim.h>
#include <PrimitiveManager.h>
#include <vector>
#include "Particle.h"

class ParticleSystem : Object
{
protected:
	graphics::ParticlesPrimitive* particlePrimitives;
	std::vector<Particle> particles;

	glm::vec3 startVelocity;

	void Update();
	glm::vec3 EulerSolver(glm::vec3 x0, glm::vec3 v0, float dt);
public:
	ParticleSystem(int num);
};

