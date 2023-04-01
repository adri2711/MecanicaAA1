#include "ClothSim.h"

#include <iostream>

ClothSim::ClothSim()
{
	_meshSystem = new MeshSystem(MIN_DISTANCE_BETWEEN_PARTICLES, MIN_STRUCTURAL_ELASTICITY, MIN_STRUCTURAL_DAMPING,
		MIN_SHEAR_ELASTICITY, MIN_SHEAR_DAMPING, MIN_BEND_ELASTICITY, MIN_BEND_DAMPING);
	_colliderSystem = new ColliderSystem();

	srand(time(NULL));		

	float sphereXPosition = 8 * ((float)rand() / (float)RAND_MAX) + -4;
	float sphereYPosition = rand()% 7;
	float sphereZPosition = 7 * ((float)rand() / (float)RAND_MAX) + -3;

	std::cout << sphereXPosition << std::endl;
	
	Sphere* sphere = new Sphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f);	
	AddCollider(sphere);	
	
	AddCollider(new Plane(glm::vec3(-5.f, 0.f, 5.f), glm::vec3(10.f, 0.f, 10.f))); 
	AddCollider(new Plane(glm::vec3(5.f, 0.f, -5.f), glm::vec3(0.f, 10.f, 10.f))); 
	AddCollider(new Plane(glm::vec3(5.f, 10.f, -5.f), glm::vec3(10.f, 0.f, 10.f))); 
	AddCollider(new Plane(glm::vec3(-5.f, 0.f, -5.f), glm::vec3(0.f, 10.f, 10.f)));
	AddCollider(new Plane(glm::vec3(-5.f, 10.f, -5.f), glm::vec3(10.f, 10.f, 0.f)));
	AddCollider(new Plane(glm::vec3(5.f, 10.f, 5.f), glm::vec3(10.f, 10.f, 0.f)));
	
	_colliderSystem->SetSphere(sphere);
}

ClothSim::~ClothSim()
{	
	delete _meshSystem;
	delete _colliderSystem;
}

void ClothSim::Update(float dt)
{
	_meshSystem->UpdateMesh(_colliders, dt);	

	_currentTime -= dt;

	if (_currentTime <= 0.0f)
	{
		_currentTime = _initialTime;
		float distanceBetweenParticles = _meshSystem->GetMesh()->GetDistanceBetweenParticles();
		
		float structuralElasticity = _meshSystem->GetMesh()->GetStructuralElasticity();
		float structuralDamping = _meshSystem->GetMesh()->GetStructuralDamping();
		
		float shearElasticity = _meshSystem->GetMesh()->GetShearElasticity();
		float shearDamping = _meshSystem->GetMesh()->GetShearDamping();
		
		float bendElasticity = _meshSystem->GetMesh()->GetBendElasticity();
		float bendDamping = _meshSystem->GetMesh()->GetBendDamping();		

		float sphereXPosition = 8 * ((float)rand() / (float)RAND_MAX) + -4;
		float sphereYPosition = rand()% 7;
		float sphereZPosition = 7 * ((float)rand() / (float)RAND_MAX) + -3;

		_colliderSystem->~ColliderSystem();
		
		Sphere* sphere = new Sphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f);
		AddCollider(sphere);
		_colliderSystem->SetSphere(sphere);
		delete _meshSystem;
		_meshSystem = new MeshSystem(distanceBetweenParticles, structuralElasticity, structuralDamping, shearElasticity,
			shearDamping, bendElasticity, bendDamping);
	}
}

void ClothSim::RenderUpdate()
{
	_meshSystem->Draw();
	_colliderSystem->Render();
}

void ClothSim::RenderGui()
{	
	ImGui::SliderFloat("Distance Between Particles", &_meshSystem->GetMesh()->_distanceBetweenParticles, MIN_DISTANCE_BETWEEN_PARTICLES, MAX_DISTANCE_BETWEEN_PARTICLES);
	
	ImGui::SliderFloat("Structural Elasticity", &_meshSystem->GetMesh()->_structuralElasticity, MIN_STRUCTURAL_ELASTICITY, MAX_STRUCTURAL_ELASTICITY);
	ImGui::SliderFloat("Structural Damping", &_meshSystem->GetMesh()->_structuralDamping, MIN_STRUCTURAL_DAMPING, MAX_STRUCTURAL_DAMPING);
	
	ImGui::SliderFloat("Shear Elasticity", &_meshSystem->GetMesh()->_shearElasticity, MIN_SHEAR_ELASTICITY, MAX_SHEAR_ELASTICITY);
	ImGui::SliderFloat("Shear Damping", &_meshSystem->GetMesh()->_shearDamping, MIN_SHEAR_DAMPING, MAX_SHEAR_DAMPING);

	ImGui::SliderFloat("Bend Elasticity", &_meshSystem->GetMesh()->_bendElasticity, MIN_BEND_ELASTICITY, MAX_BEND_ELASTICITY);
	ImGui::SliderFloat("Bend Damping", &_meshSystem->GetMesh()->_bendDamping, MIN_BEND_DAMPING, MAX_BEND_DAMPING);
}
