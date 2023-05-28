#pragma once
#include <PrimitiveManager.h>

#include "ColliderSystem.h"
#include "Particle.h"
#include "Fluid.h"

extern graphics::PrimitiveManager manager;

class FluidSystem
{
private:

	graphics::MeshPrimitive* _meshPrimitive;
	graphics::ParticlesPrimitive* _particlePrimitive;
	std::vector<Particle> _particles;
	Fluid* _fluid;

public: 
	
	FluidSystem(float distanceBetweenParticles);
	~FluidSystem();

	Fluid* GetFluid();

	void Update(std::vector<Collider*> colliders, float dt);
	void Draw();
};

