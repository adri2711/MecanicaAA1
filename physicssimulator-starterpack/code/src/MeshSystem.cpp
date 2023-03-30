#include "MeshSystem.h"

extern graphics::PrimitiveManager manager;

MeshSystem::MeshSystem()
{
	_mesh = new Mesh(glm::vec3(-3.f, 9.f, 0.0f), MIN_DISTANCE_BETWEEN_PARTICLES);

	_meshPrimitive = manager.NewMesh(MIN_HEIGHT_LENGTH, MIN_WIDTH_LENGTH);	
}

MeshSystem::~MeshSystem()
{
	manager.DestroyPrimitive(_meshPrimitive);
}

void MeshSystem::UpdateMesh(float dt)
{
	_mesh->UpdatePosition(dt);
}

void MeshSystem::Draw()
{	
	_meshPrimitive->Update(_mesh->GetFirstPosition());
}
