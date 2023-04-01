#pragma once
#include <PrimitiveManager.h>

#include "ColliderSystem.h"
#include "Particle.h"
#include "Mesh.h"

extern graphics::PrimitiveManager manager;

class MeshSystem
{
private:

	graphics::MeshPrimitive* _meshPrimitive;
	graphics::ParticlesPrimitive* _particlePrimitive;
	std::vector<Particle> _particles;
	Mesh* _mesh;

public: 
	
	MeshSystem(float distanceBetweenParticles, float structuralElasticity, float structuralDamping,
	float shearElasticity, float shearDamping, float bendElasticity, float bendDamping);
	~MeshSystem();

	Mesh* GetMesh();

	void UpdateMesh(std::vector<Collider*> colliders, float dt);
	void Draw();
};

