#include "MeshSystem.h"

extern graphics::PrimitiveManager manager;

MeshSystem::MeshSystem()
{
	_mesh = new Mesh(glm::vec3(-3.f, 9.f, 0.0f), MIN_DISTANCE_BETWEEN_PARTICLES, 0.01f, 0.01f, 0.01f, 0.01f);

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
}

void MeshSystem::Draw()
{	
	_meshPrimitive->Update(_mesh->GetFirstPosition());
}
