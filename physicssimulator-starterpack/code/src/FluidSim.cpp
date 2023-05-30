#include "FluidSim.h"

#include <iostream>

void FluidSim::Reset()
{
	_currentTime = _initialTime;
	float distanceBetweenParticles = _fluidSystem->GetFluid()->distanceBetweenParticles;

	delete _colliderSystem;

	_colliderSystem = new ColliderSystem();

	float sphereXPosition = 4 * ((float)rand() / (float)RAND_MAX) + -2;
	float sphereYPosition = 6 * ((float)rand() / (float)RAND_MAX) + 2;
	float sphereZPosition = 3 * ((float)rand() / (float)RAND_MAX) + 0;

	_sphere = new BuoyantSphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f, 5.f);
	AddCollider(_sphere);
	_colliderSystem->SetSphere(_sphere);

	delete _fluidSystem;
	_fluidSystem = new FluidSystem(distanceBetweenParticles);
}

FluidSim::FluidSim()
{
	_fluidSystem = new FluidSystem(MIN_DISTANCE_BETWEEN_PARTICLES);
	_colliderSystem = new ColliderSystem();

	srand(time(NULL));		

	float sphereXPosition = 4 * ((float)rand() / (float)RAND_MAX) + -2;
	float sphereYPosition = 6 * ((float)rand() / (float)RAND_MAX) + 2;
	float sphereZPosition = 3 * ((float)rand() / (float)RAND_MAX) + 0;
	
	_sphere = new BuoyantSphere(glm::vec3(sphereXPosition, sphereYPosition, sphereZPosition), 1.f, 5.f);
	AddCollider(_sphere);	
	_colliderSystem->SetSphere(_sphere);
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
		//Update systems
		_fluidSystem->Update(_colliders, dt / DT_DIVISOR);

		_sphere->ApplyBuoyancyForce(_fluidSystem->GetFluid()->density, _fluidSystem->GetFluid()->FindSubmergedVolume(*_sphere));
		_sphere->Update(dt / DT_DIVISOR);

		if (!stopReset) {
			_currentTime -= dt / DT_DIVISOR;
		}

		//Reset Sim
		if (_currentTime <= 0.0f)
		{
			Reset();
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
	if (ImGui::Button("Reset")) {
		Reset();
	}
	if (ImGui::Button("Toggle Auto-Reset")) {
		stopReset = !stopReset;
	}
	ImGui::Text("Sphere:");
	ImGui::SliderFloat("Mass", &_sphere->mass, MIN_MASS, MAX_MASS);
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
