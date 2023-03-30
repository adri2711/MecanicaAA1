#pragma once
#include <PrimitiveManager.h>
#include "Particle.h"
#include "Mesh.h"

extern graphics::PrimitiveManager manager;

class MeshSystem
{
private: 

	graphics::MeshPrimitive* _meshPrimitive;
	graphics::ParticlesPrimitive* particlePrimitives;
	std::vector<Particle> particles;
	Mesh* _mesh;

public: 
	
	MeshSystem();
	~MeshSystem();

	void UpdateMesh(float dt);
	void Draw();
};

