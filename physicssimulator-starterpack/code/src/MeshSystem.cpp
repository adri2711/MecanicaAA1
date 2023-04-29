#include "MeshSystem.h"

extern graphics::PrimitiveManager manager;

MeshSystem::MeshSystem(float distanceBetweenParticles, float structuralElasticity, float structuralDamping,
	float shearElasticity, float shearDamping, float bendElasticity, float bendDamping)
{
	_mesh = new Mesh(glm::vec3(-3.f, 9.f, 4.0f), distanceBetweenParticles,
		structuralElasticity, structuralDamping, shearElasticity, shearDamping,
		bendElasticity, bendDamping);

	_meshPrimitive = manager.NewMesh(HEIGHT, WIDTH);

	for (int i = 0; i < _mesh->GetPositions().size(); ++i)
	{
		_particles.push_back(Particle(_mesh->GetPositions()[i], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), 20.f, 1.f));
	}
	
	_particlePrimitive = manager.NewParticles(_particles.size());
	_particlePrimitive->numParticles = _particles.size();
}

MeshSystem::~MeshSystem()
{
	manager.DestroyPrimitive(_meshPrimitive);
	manager.DestroyPrimitive(_particlePrimitive);
	//delete _mesh;
}

Mesh* MeshSystem::GetMesh()
{
	return _mesh;
}

void MeshSystem::UpdateMesh(std::vector<Collider*> colliders, float dt)
{
	_mesh->UpdateNodesPositions(colliders, dt);
}

void MeshSystem::Draw()
{	
	_meshPrimitive->Update(_mesh->GetFirstPosition());
	_particlePrimitive->Update(0, _particles.size(), &_mesh->GetPositions()[0].x);
}
