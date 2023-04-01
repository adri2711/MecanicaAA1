#include "MeshSystem.h"

extern graphics::PrimitiveManager manager;

MeshSystem::MeshSystem()
{
	_mesh = new Mesh(glm::vec3(-3.f, 9.f, 0.0f), MIN_DISTANCE_BETWEEN_PARTICLES,
		MIN_STRUCTURAL_ELASTICITY, MIN_STRUCTURAL_DAMPING, MIN_SHEAR_ELASTICITY, MIN_SHEAR_DAMPING,
		MIN_BEND_ELASTICITY, MIN_BEND_DAMPING);

	_meshPrimitive = manager.NewMesh(HEIGHT, WIDTH);
}

MeshSystem::~MeshSystem()
{
	manager.DestroyPrimitive(_meshPrimitive);
	manager.DestroyPrimitive(_particlePrimitives);
}

Mesh* MeshSystem::GetMesh()
{
	return _mesh;
}

void MeshSystem::UpdateMesh(float dt)
{
	_mesh->UpdateNodesPositions(dt);

	currentTime += dt;

	if (currentTime >= 3.0f)
	{
		currentTime = 0.f;
	}
}

void MeshSystem::Draw()
{	
	_meshPrimitive->Update(_mesh->GetFirstPosition());
}
