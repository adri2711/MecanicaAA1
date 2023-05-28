#include "FluidSim.h"

#include <iostream>

FluidSim::FluidSim()
{
	_fluidSystem = new FluidSystem(MIN_DISTANCE_BETWEEN_PARTICLES);
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

FluidSim::~FluidSim()
{	
	delete _fluidSystem;
	delete _colliderSystem;
}

void FluidSim::Update(float dt)
{
	for (int i = 0; i < DT_DIVISOR; i++)
	{
		_fluidSystem->Update(_colliders, dt / DT_DIVISOR);

		_currentTime -= dt / DT_DIVISOR;

		if (_currentTime <= 0.0f)
		{
			_currentTime = _initialTime;
			float distanceBetweenParticles = _fluidSystem->GetFluid()->distanceBetweenParticles;	

			delete _colliderSystem;

			_colliderSystem = new ColliderSystem();			

			float sphereXPosition = 4 * ((float)rand() / (float)RAND_MAX) + -2;
			float sphereYPosition = 6 * ((float)rand() / (float)RAND_MAX) + 2;
			float sphereZPosition = 3 * ((float)rand() / (float)RAND_MAX) + 0;

			Sphere* sphere = new Sphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f);
			AddCollider(sphere);
			_colliderSystem->SetSphere(sphere);
			
			delete _fluidSystem;
			_fluidSystem = new FluidSystem(distanceBetweenParticles);
		}
	}	
}

void FluidSim::RenderUpdate()
{
	_fluidSystem->Draw();
	_colliderSystem->Render();
}

void FluidSim::RenderGui()
{	
}
