#include "ClothSim.h"

ClothSim::ClothSim()
{
	_meshSystem = new MeshSystem();
	//_colliderSystem = new ColliderSystem();
}

ClothSim::~ClothSim()
{	
	delete _meshSystem;
}

void ClothSim::Update(float dt)
{
	_meshSystem->UpdateMesh(dt);
}

void ClothSim::RenderUpdate()
{
	_meshSystem->Draw();
}

void ClothSim::RenderGui()
{
}
