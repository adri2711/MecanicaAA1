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
	
	ImGui::SliderFloat("Structural Elasticity", &_meshSystem->GetMesh()->_structuralElasticity, MIN_STRUCTURAL_ELASTICITY, MAX_STRUCTURAL_ELASTICITY);
	ImGui::SliderFloat("Structural Damping", &_meshSystem->GetMesh()->_structuralDamping, MIN_STRUCTURAL_DAMPING, MAX_STRUCTURAL_DAMPING);
	
	ImGui::SliderFloat("Shear Elasticity", &_meshSystem->GetMesh()->_shearElasticity, MIN_SHEAR_ELASTICITY, MAX_SHEAR_ELASTICITY);
	ImGui::SliderFloat("Shear Damping", &_meshSystem->GetMesh()->_shearElasticity, MIN_SHEAR_DAMPING, MAX_SHEAR_DAMPING);

	ImGui::SliderFloat("Bend Elasticity", &_meshSystem->GetMesh()->_bendElasticity, MIN_BEND_ELASTICITY, MAX_BEND_ELASTICITY);
	ImGui::SliderFloat("Bend Damping", &_meshSystem->GetMesh()->_bendElasticity, MIN_BEND_DAMPING, MAX_BEND_DAMPING);
}
