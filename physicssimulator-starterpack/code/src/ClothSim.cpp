#include "ClothSim.h"

#include <iostream>

ClothSim::ClothSim()
{
	_meshSystem = new MeshSystem(MIN_DISTANCE_BETWEEN_PARTICLES, MAX_STRUCTURAL_RIGIDITY, MIN_STRUCTURAL_DAMPING,
		MAX_SHEAR_RIGIDITY, MIN_SHEAR_DAMPING, MAX_BEND_RIGIDITY, MIN_BEND_DAMPING);
	_colliderSystem = new ColliderSystem();

	srand(time(NULL));		

	float sphereXPosition = 4 * ((float)rand() / (float)RAND_MAX) + -2;
	float sphereYPosition = 6 * ((float)rand() / (float)RAND_MAX) + 2;
	float sphereZPosition = 3 * ((float)rand() / (float)RAND_MAX) + 0;
	
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
	for (int i = 0; i < DT_DIVISOR; i++)
	{
		_meshSystem->UpdateMesh(_colliders, dt / DT_DIVISOR);

		_currentTime -= dt / DT_DIVISOR;

		if (_currentTime <= 0.0f)
		{
			_currentTime = _initialTime;
			float distanceBetweenParticles = _meshSystem->GetMesh()->GetDistanceBetweenParticles();

			float structuralElasticity = _meshSystem->GetMesh()->GetStructuralRigidity();
			float structuralDamping = _meshSystem->GetMesh()->GetStructuralDamping();

			float shearElasticity = _meshSystem->GetMesh()->GetShearRigidity();
			float shearDamping = _meshSystem->GetMesh()->GetShearDamping();

			float bendElasticity = _meshSystem->GetMesh()->GetBendRigidity();
			float bendDamping = _meshSystem->GetMesh()->GetBendDamping();			

			delete _colliderSystem;

			_colliderSystem = new ColliderSystem();			

			float sphereXPosition = 4 * ((float)rand() / (float)RAND_MAX) + -2;
			float sphereYPosition = 6 * ((float)rand() / (float)RAND_MAX) + 2;
			float sphereZPosition = 3 * ((float)rand() / (float)RAND_MAX) + 0;

			Sphere* sphere = new Sphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f);
			AddCollider(sphere);
			_colliderSystem->SetSphere(sphere);
			
			delete _meshSystem;
			_meshSystem = new MeshSystem(distanceBetweenParticles, structuralElasticity, structuralDamping, shearElasticity,
				shearDamping, bendElasticity, bendDamping);
		}
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
	
	ImGui::SliderFloat("Structural Rigidity", &_meshSystem->GetMesh()->_structuralRigidity, MIN_STRUCTURAL_RIGIDITY, MAX_STRUCTURAL_RIGIDITY);
	ImGui::SliderFloat("Structural Damping", &_meshSystem->GetMesh()->_structuralDamping, MIN_STRUCTURAL_DAMPING, MAX_STRUCTURAL_DAMPING);
	
	ImGui::SliderFloat("Shear Rigidity", &_meshSystem->GetMesh()->_shearRigidity, MIN_SHEAR_RIGIDITY, MAX_SHEAR_RIGIDITY);
	ImGui::SliderFloat("Shear Damping", &_meshSystem->GetMesh()->_shearDamping, MIN_SHEAR_DAMPING, MAX_SHEAR_DAMPING);

	ImGui::SliderFloat("Bend Rigidity", &_meshSystem->GetMesh()->_bendRigidity, MIN_BEND_RIGIDITY, MAX_BEND_RIGIDITY);
	ImGui::SliderFloat("Bend Damping", &_meshSystem->GetMesh()->_bendDamping, MIN_BEND_DAMPING, MAX_BEND_DAMPING);
}
