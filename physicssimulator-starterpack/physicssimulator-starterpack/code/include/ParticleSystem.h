#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <PrimitiveManager.h>
#include <vector>
#include "Particle.h"

class ParticleSystem : public Object
{
protected:
	graphics::ParticlesPrimitive* particlePrimitives;
	std::vector<Particle> particles;

	const glm::vec3 gravity = { 0, -9.81f, 0 };
	glm::vec3 startVelocity = {0, 10.f, 0};

	glm::vec3 EulerSolver(glm::vec3 x0, glm::vec3 v0, float dt);
public:
	ParticleSystem() : Object(glm::vec3(0, 0, 0)) {}
	~ParticleSystem();
	void Setup(int num);
	void Update(float dt);
	void Render();
};

