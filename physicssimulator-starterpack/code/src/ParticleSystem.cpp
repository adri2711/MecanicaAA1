#include "ParticleSystem.h"

#include <iostream>

#include "Sphere.h"

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
	
	Plane* plane = (CheckColliders(i, nextPosition, colliders));
		
	if (plane != nullptr) {

		PositionAfterCollision(i, nextPosition, plane->GetNormal(), plane->GetD());
		VelocityAfterCollision(i, nextVelocity, plane->GetNormal());		
	}
	else
	{	
		particles[i].position = nextPosition;
		particles[i].velocity = nextVelocity;				
	}
	
	positions[i] = particles[i].position;
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

Plane* ParticleSystem::CheckColliders(int i, glm::vec3 nextPosition, std::vector<Collider*> colliders) const
{
	for (int j = 0; j < colliders.size(); j++)
	{
		Collider* collider = colliders[j];

		if (collider->GetColliderType() == PLANE)
		{
			Plane* plane = reinterpret_cast<Plane*>(collider);
			float d = plane->GetD();
			glm::vec3 normal = plane->GetNormal();
			glm::vec3 currentPosition = particles[i].position;

			if ((glm::dot(normal, currentPosition) + d) * (glm::dot(normal, nextPosition) + d) <= 0.f)
			{
				return plane;				
			}
			
			continue;
			
		}
		else if (collider->GetColliderType() == SPHERE)
		{

			Sphere* sphere = reinterpret_cast<Sphere*>(collider);
			
			glm::vec3 vectorToSphereCenter = sphere->GetCoordinates() - nextPosition;
			
			if (sqrt(glm::dot(vectorToSphereCenter, vectorToSphereCenter)) <= sphere->GetRadius())
			{
				glm::vec3 currentPosition = particles[i].position;
				glm::vec3 vectorBetweenPositions = nextPosition - currentPosition;
				
				float a = sphere->CalculateA(currentPosition);
				float b = sphere->CalculateB(currentPosition, vectorBetweenPositions);
				float c = sphere->CalculateC(vectorBetweenPositions);
				float d = a + b + c;

				float result1 = (-b + sqrt(pow(b,2) - 4 * a * (c - d))) / 2 * a;
				float result2 = (-b - sqrt(pow(b,2) - 4 * a * (c - d))) / 2 * a;

				float alpha = fminf(result1, result2);

				glm::vec3 collisionPoint;

				collisionPoint = currentPosition + vectorBetweenPositions * alpha;

				Plane* plane = new Plane(collisionPoint);
				plane->SetNormal(collisionPoint - sphere->GetCoordinates());
				plane->CalculateD();
				
				return plane;				
			}
			
			continue;
		}
		else if (collider->GetColliderType() == CAPSULE)
		{

			//return collider;
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