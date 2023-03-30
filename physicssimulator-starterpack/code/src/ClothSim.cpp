#include "ClothSim.h"

ClothSim::ClothSim()
{
	_meshSystem = new MeshSystem();
	//_colliderSystem = new ColliderSystem();
}

ClothSim::~ClothSim()
{	
	delete _meshSystem;
	delete _colliderSystem;
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
	ImGui::SliderFloat("Distance Between Particles", &_meshSystem->GetMesh()->_distanceBetweenParticles, MIN_DISTANCE_BETWEEN_PARTICLES, MAX_DISTANCE_BETWEEN_PARTICLES);
	
	ImGui::SliderFloat("Structural Elasticity", &_meshSystem->GetMesh()->_structuralElasticity, MIN_STRUCTURAL_CONSTANT, MAX_STRUCTURAL_CONSTANT);
	ImGui::SliderFloat("Shear Elasticity", &_meshSystem->GetMesh()->_shearElasticity, MIN_SHEAR_CONSTANT, MAX_SHEAR_CONSTANT);
	ImGui::SliderFloat("Bend Elasticity", &_meshSystem->GetMesh()->_bendElasticity, MIN_BEND_CONSTANT, MAX_BEND_CONSTANT);
}
