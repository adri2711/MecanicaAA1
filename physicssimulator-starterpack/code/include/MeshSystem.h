#pragma once
#include <PrimitiveManager.h>
#include "Particle.h"
#include "Mesh.h"

extern graphics::PrimitiveManager manager;

class MeshSystem
{
private:

	float currentTime = 0.f;

	graphics::MeshPrimitive* _meshPrimitive;
	graphics::ParticlesPrimitive* _particlePrimitives;
	std::vector<Particle> particles;
	Mesh* _mesh;

public: 
	
	MeshSystem();
	~MeshSystem();

	Mesh* GetMesh();

	void UpdateMesh(float dt);
	void Draw();
};

