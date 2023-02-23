#include "ParticleSystem.h"

extern graphics::PrimitiveManager manager;

void ParticleSystem::Update()
{

}

glm::vec3 ParticleSystem::EulerSolver(glm::vec3 x0, glm::vec3 v0, float dt)
{
	return x0 + v0 * dt;
}

ParticleSystem::ParticleSystem(int num)
{
	particlePrimitives = manager.NewParticles(num);
}
