#include "ParticleSystem.h"

extern graphics::PrimitiveManager manager;

void ParticleSystem::Update(float dt)
{
	emitTime += dt;
	if (emitTime >= 1.f/emissionRate) {
		EmitParticles();
		emitTime -= 1.f/emissionRate;
	}

	positions = new glm::vec3[particles.size()];
	for (int i = 0; i < particles.size(); i++) {
		ParticleUpdate(i, dt);
	}
}

void ParticleSystem::Render() {
	if (particles.empty()) return;
	particlePrimitives->firstParticle = 0;
	particlePrimitives->numParticles = particles.size();
	particlePrimitives->Update(0, particles.size(), &(positions[0].x));
	delete[] positions;
}

glm::vec3 ParticleSystem::EulerSolver(glm::vec3 x0, glm::vec3 v0, float dt)
{
	return x0 + v0 * dt;
}

void ParticleSystem::ParticleUpdate(int i, float dt)
{
	particles[i].velocity = EulerSolver(particles[i].velocity, particles[i].acceleration, dt);
	particles[i].position = EulerSolver(particles[i].position, particles[i].velocity, dt);
	positions[i] = particles[i].position;

	particles[i].time += dt;
	if (particles[i].time >= particles[i].lifeTime) {
		DeleteParticle(i);
	}
}

Particle ParticleSystem::CreateParticle()
{
	return Particle(position, startVelocity, gravity, particleLifeTime, particleMass);
}

void ParticleSystem::DeleteParticle(int i)
{
	particles.erase(particles.begin() + i);
	UpdatePrimitive();
}

void ParticleSystem::EmitParticles()
{
	for (int i = 0; i < emissionCount; i++) {
		particles.push_back(CreateParticle());
	}
	UpdatePrimitive();
}

void ParticleSystem::UpdatePrimitive()
{
	manager.DestroyPrimitive(particlePrimitives);
	particlePrimitives = manager.NewParticles(particles.size());
}

void ParticleSystem::Setup()
{
	emitTime = emissionRate;
}

ParticleSystem::~ParticleSystem()
{
	manager.DestroyPrimitive(particlePrimitives);
}
