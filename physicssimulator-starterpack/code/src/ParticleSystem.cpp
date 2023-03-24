#include "ParticleSystem.h"

#include <iostream>

#include "Capsule.h"
#include "Capsule.h"
#include "Capsule.h"
#include "Capsule.h"
#include "Capsule.h"
#include "Capsule.h"
#include "Capsule.h"
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
		}
		else if (collider->GetColliderType() == SPHERE)
		{
			Plane* plane = CalculateSpherePlane(i, nextPosition, collider);

			if (plane != nullptr)
			{
				return plane;
			}
			
		}
		else if (collider->GetColliderType() == CAPSULE)
		{

			Capsule* capsule = reinterpret_cast<Capsule*>(collider);

			glm::vec3 pointA = capsule->_pointACoordinates;
			glm::vec3 pointB = capsule->_pointBCoordinates;

			glm::vec3 nextPositionClosestPoint = CalculateClosestPointBetweenPointAndCapsule(nextPosition, capsule, pointA, pointB);
			
			if (CalculateDistanceBetweenPointAndCapsule(nextPosition, capsule, nextPositionClosestPoint) <= 0.f)
			{
				
				glm::vec3 currentPosition = particles[i].position;
				glm::vec3 currentPositionClosestPoint = CalculateClosestPointBetweenPointAndCapsule(currentPosition, capsule, pointA, pointB);
				
				glm::vec3 midPoint = currentPosition + (nextPosition - currentPosition) / 2.f;

				float distanceToCapsule;
				
				glm::vec3 upperBound = midPoint - currentPosition;
				glm::vec3 lowerBound = midPoint - nextPosition;

				bool _pointFound;
				
				do
				{

					glm::vec3 midPointClosestPoint = CalculateClosestPointBetweenPointAndCapsule(midPoint, capsule, pointA, pointB);

					distanceToCapsule = CalculateDistanceBetweenPointAndCapsule(midPoint, capsule, midPointClosestPoint);
					
					_pointFound = true;
					
					if (distanceToCapsule > 0.1f)
					{
						upperBound /= 2;
						midPoint = upperBound;
						_pointFound = false;
					}
					else if (distanceToCapsule < -0.1f)
					{
						lowerBound /= 2;
						midPoint = lowerBound;
						_pointFound = false;
					}
					
				}while (!_pointFound);

				Sphere* sphere = new Sphere(midPoint, capsule->_radius);

				return CalculateSpherePlane(i, nextPosition, sphere);				
			}
		}
	}
	return nullptr;
}

glm::vec3 ParticleSystem::CalculateClosestPointBetweenPointAndCapsule(glm::vec3 position, Capsule* capsule, glm::vec3 pointA, glm::vec3 pointB) const
{
	float a = glm::dot(position - pointA, pointB - pointA);
	float b = pow(sqrt(glm::dot(pointB - pointA, pointB - pointA)), 2);
	
	float clamp = glm::clamp(a / b, 0.f, 1.f);
	
	return pointA + clamp * (pointB - pointA);	
}

float ParticleSystem::CalculateDistanceBetweenPointAndCapsule(glm::vec3 position, Capsule* capsule, glm::vec3 closestPoint) const
{
	return sqrt(glm::dot(position - closestPoint, position - closestPoint)) - capsule->_radius;
}


Plane* ParticleSystem::CalculateSpherePlane(int i, glm::vec3 nextPosition, Collider* collider) const
{
	Sphere* sphere = reinterpret_cast<Sphere*>(collider);
			
	glm::vec3 vectorToSphereCenter = sphere->_coordinates - nextPosition;
			
	if (sqrt(glm::dot(vectorToSphereCenter, vectorToSphereCenter)) <= sphere->_radius)
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

		glm::vec3 collisionPoint = currentPosition + vectorBetweenPositions * alpha;

		Plane* plane = new Plane(collisionPoint);
		plane->SetNormal(collisionPoint - sphere->_coordinates);
		plane->CalculateD();

		return plane;				
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