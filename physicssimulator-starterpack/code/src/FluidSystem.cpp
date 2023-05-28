#include "FluidSystem.h"

extern graphics::PrimitiveManager manager;

FluidSystem::FluidSystem(float distanceBetweenParticles)
{
	_fluid = new Fluid(glm::vec3(-3.f, 9.f, 4.0f), distanceBetweenParticles);

	_meshPrimitive = manager.NewMesh(HEIGHT, WIDTH);

	for (int i = 0; i < _fluid->GetPositions().size(); ++i)
	{
		_particles.push_back(Particle(_fluid->GetPositions()[i], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), 20.f, 1.f));
	}
	
	_particlePrimitive = manager.NewParticles(_particles.size());
	_particlePrimitive->numParticles = _particles.size();
}

FluidSystem::~FluidSystem()
{
	manager.DestroyPrimitive(_meshPrimitive);
	manager.DestroyPrimitive(_particlePrimitive);
}

Fluid* FluidSystem::GetFluid()
{
	return _fluid;
}

void FluidSystem::Update(std::vector<Collider*> colliders, float dt)
{
	_fluid->UpdateNodesPositions(colliders, dt);
}

void FluidSystem::Draw()
{	
	_meshPrimitive->Update(_fluid->GetFirstPosition());
	_particlePrimitive->Update(0, _particles.size(), &_fluid->GetPositions()[0].x);
}
