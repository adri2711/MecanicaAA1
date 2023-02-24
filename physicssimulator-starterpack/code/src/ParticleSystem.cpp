#include "ParticleSystem.h"

extern graphics::PrimitiveManager manager;

void ParticleSystem::Update(float dt)
{
	glm::vec3* positions;
	positions = new glm::vec3[particles.size()];
	//Logic
	for (int i = 0; i < particles.size(); i++) {
		particles[i].velocity = EulerSolver(particles[i].velocity, particles[i].acceleration, dt);
		particles[i].position = EulerSolver(particles[i].position, particles[i].velocity, dt);
		positions[i] = particles[i].position;
	}

	//Render
	particlePrimitives->firstParticle = 0;
	particlePrimitives->numParticles = particles.size();
	particlePrimitives->Update(0, particles.size(), &(positions[0].x));

	delete[] positions;
}

void ParticleSystem::Render() {

}

glm::vec3 ParticleSystem::EulerSolver(glm::vec3 x0, glm::vec3 v0, float dt)
{
	return x0 + v0 * dt;
}

void ParticleSystem::Setup(int num)
{
	particlePrimitives = manager.NewParticles(num);
	for (int i = 0; i < num; i++) {
		particles.push_back(Particle(position, startVelocity, gravity));
	}
}

ParticleSystem::~ParticleSystem()
{
	manager.DestroyPrimitive(particlePrimitives);
}
