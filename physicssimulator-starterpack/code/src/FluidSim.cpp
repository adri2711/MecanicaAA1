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
	
	BuoyantSphere* sphere = new BuoyantSphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f, 1.f);
	AddCollider(sphere);	
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

			BuoyantSphere* sphere = new BuoyantSphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f, 1.f);
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
	if (_fluidSystem->GetFluid()->_waves.size() < 10 && ImGui::Button("Add Wave")) {
		_fluidSystem->GetFluid()->AddWave(DEFAULT_WAVE);
	}
	for (int i = 0; i < _fluidSystem->GetFluid()->_waves.size(); i++) {
		for (int t = 0; t < labels.size(); t++) {
			labels[t][12] = i + '0';
		}
		ImGui::Text(labels[0].c_str());
		ImGui::SliderFloat(labels[1].c_str(), &_fluidSystem->GetFluid()->_waves[i].angle, MIN_ANGLE, MAX_ANGLE);
		ImGui::SliderFloat(labels[2].c_str(), &_fluidSystem->GetFluid()->_waves[i].amplitude, MIN_AMPLITUDE, MAX_AMPLITUDE);
		ImGui::SliderFloat(labels[3].c_str(), &_fluidSystem->GetFluid()->_waves[i].wavelength, MIN_WAVELENGTH, MAX_WAVELENGTH);
		ImGui::SliderFloat(labels[4].c_str(), &_fluidSystem->GetFluid()->_waves[i].phi, MIN_PHASE, MAX_PHASE);
	}
}
