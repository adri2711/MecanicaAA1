#include "ParticleSystem.h"

#include <iostream>

extern graphics::PrimitiveManager manager;

void ParticleSystem::Update(float dt, std::vector<Collider*> colliders)
{
	float emission = 1.f / emissionRate;
	emitTime += dt;
	if (emitTime >= emission) {
		int amount = dt / emission;
		EmitParticles(amount);
		emitTime -= amount * emission;
	}

	positions = new glm::vec3[particles.size()];
	for (int i = 0; i < particles.size(); i++) {
		ParticleUpdate(i, dt, colliders);
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

void ParticleSystem::ParticleUpdate(int i, float dt, std::vector<Collider*> colliders)
{
	particles[i].time += dt;
	if (particles[i].time >= particles[i].lifeTime) {
		DeleteParticle(i);
		return;
	}

	glm::vec3 nextVelocity = EulerSolver(particles[i].velocity, particles[i].acceleration, dt);
	glm::vec3 nextPosition = EulerSolver(particles[i].position, particles[i].velocity, dt);

	CheckCollisions(i, nextPosition, nextVelocity, colliders);
}

Particle ParticleSystem::CreateParticle()
{
	return Particle(position, startVelocity, gravity, particleLifeTime, particleMass);
}

void ParticleSystem::CheckCollisions(int i, glm::vec3 nextPosition, glm::vec3 nextVelocity, std::vector<Collider*> colliders)
{	
	Collider* collider = CheckColliders(i, nextPosition, nextVelocity, colliders);
	
	if (collider != nullptr) {

		if (collider->GetColliderType() == PLANE)
		{
			PositionAfterCollision(i, nextPosition, collider->GetNormal(), collider->GetD());
			VelocityAfterCollision(i, nextVelocity, collider->GetNormal());
			//CheckCollisions(i, particles[i].position, particles[i].velocity, colliders);
		}
		else if (collider->GetColliderType() == SPHERE)
		{

			//Plane* auxCollider = reinterpret_cast<Plane*>(collider);
		}
		else if (collider->GetColliderType() == CAPSULE)
		{

			//Plane* auxCollider = reinterpret_cast<Plane*>(collider);
		}		
	}
	else
	{	
		particles[i].position = nextPosition;
		particles[i].velocity = nextVelocity;				
	}
	
	positions[i] = particles[i].position;
}

void ParticleSystem::DeleteParticle(int i)
{
	particles.erase(particles.begin() + i);
	UpdatePrimitive();
}

void ParticleSystem::EmitParticles(int emissionCount)
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
	particlePrimitives->numParticles = particles.size();
}

Collider* ParticleSystem::CheckColliders(int i, glm::vec3 nextPosition, glm::vec3 nextVelocity, std::vector<Collider*> colliders) const
{
	for (int j = 0; j < colliders.size(); j++)
	{
		Collider* collider = colliders[j];

		if (colliders[j]->GetColliderType() == PLANE)
		{
			float d = collider->GetD();
			glm::vec3 normal = collider->GetNormal();
			glm::vec3 currentPosition = particles[i].position;

			if (!((glm::dot(normal, currentPosition) + d) * (glm::dot(normal, nextPosition) + d) <= 0.f))
			{
				continue;
			}
			
			return collider;
		}
		else if (colliders[j]->GetColliderType() == SPHERE)
		{

			return collider;
		}
		else if (colliders[j]->GetColliderType() == CAPSULE)
		{

			return collider;
		}
	}

	return nullptr;
}

void ParticleSystem::PositionAfterCollision(int i, glm::vec3 nextPosition, glm::vec3 normal, float d) {
	
	particles[i].position = nextPosition - 2.f * ((glm::dot(normal, nextPosition) + d) * normal);	
}

void ParticleSystem::VelocityAfterCollision(int i, glm::vec3 nextVelocity, glm::vec3 normal) {
		
	particles[i].velocity = nextVelocity - 2.f * (glm::dot(normal, nextVelocity) * normal);
}

void ParticleSystem::Setup()
{
	emitTime = emissionRate;
}

ParticleSystem::~ParticleSystem()
{
	manager.DestroyPrimitive(particlePrimitives);
}