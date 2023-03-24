#pragma once
#include <RenderPrims.h>
#include <PrimitiveManager.h>
#include <vector>

#include "Capsule.h"
#include "Particle.h"
#include "Plane.h"


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
	virtual void ParticleUpdate(int i, float dt, std::vector<Collider*> colliders);
	virtual Particle CreateParticle();
	virtual void DeleteParticle(int i);
	void EmitParticles(int emissionCount);
	void UpdatePrimitive();	
	Plane* CheckColliders(int i, glm::vec3 nextPosition, std::vector<Collider*> colliders) const;
	void PositionAfterCollision(int i, glm::vec3 newPosition, glm::vec3 normal, float d);
	void VelocityAfterCollision(int i, glm::vec3 nextVelocity, glm::vec3 normal);
	Plane* CalculateSpherePlane(int i, glm::vec3 nextPosition, Collider* collider) const;
	glm::vec3 CalculateClosestPointBetweenPointAndCapsule(glm::vec3 position, Capsule* capsule, glm::vec3 pointA, glm::vec3 pointB) const;	
	float CalculateDistanceBetweenPointAndCapsule(glm::vec3 position, Capsule* capsule, glm::vec3 closestPoint) const;	

public:
	glm::vec3 startVelocity = { 0.f, 0.f, 0.f };
	float emissionRate = 100.f;
	float particleMass = 1.f;
	float particleLifeTime = 5.f;

	ParticleSystem() : Object(glm::vec3(0, 0, 0)) {}
	~ParticleSystem();
	virtual void Setup();
	virtual void Update(float dt, std::vector<Collider*> colliders);
	virtual void Render();
};

