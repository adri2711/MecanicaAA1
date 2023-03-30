#include <ParticleSim.h>
#include <imgui/imgui.h>
#include "FountainParticleSystem.h"
#include "CascadeParticleSystem.h"
#include "Plane.h"
#include "Sphere.h"
#include "Capsule.h"

#include <iostream>

ParticleSim::ParticleSim() {
	particleSystems.push_back(new FountainParticleSystem());
	particleSystems[0]->position = glm::vec3(2, 4, 0);
	particleSystems[0]->emissionRate = 1000.f;
	particleSystems[0]->particleLifeTime = 2.f;
	static_cast<FountainParticleSystem*>(particleSystems[0])->angle = 30.f;
	static_cast<FountainParticleSystem*>(particleSystems[0])->velocityMagnitude = 7.f;
	static_cast<FountainParticleSystem*>(particleSystems[0])->SetDirection(glm::vec3(0.3f, 1.0f, 0.f));
	particleSystems[0]->Setup();

	particleSystems.push_back(new CascadeParticleSystem());
	particleSystems[1]->position = glm::vec3(-2, 4, 0);
	particleSystems[1]->emissionRate = 1000.f;
	particleSystems[1]->particleLifeTime = 2.f;
	static_cast<CascadeParticleSystem*>(particleSystems[1])->rotationAngle = 60.f;
	static_cast<CascadeParticleSystem*>(particleSystems[1])->velocityMagnitude = 7.f;
	static_cast<CascadeParticleSystem*>(particleSystems[1])->SetPoints(glm::vec3(-1.f, 3.f, 2.f), glm::vec3(-2.f, 4.f, -2.f));
	particleSystems[1]->Setup();

	Sphere* sphere = new Sphere(glm::vec3(3.f, 3.f, 2.f), 1.f);	
	AddCollider(sphere);

	Capsule* capsule = new Capsule(glm::vec3(2.f, 3.f, -3.f), glm::vec3(-1.f, 1.f, 0.f), 1.f);                        
	AddCollider(capsule);
	
	AddCollider(new Plane(glm::vec3(-5.f, 0.f, 5.f), glm::vec3(10.f, 0.f, 10.f))); 
	AddCollider(new Plane(glm::vec3(5.f, 0.f, -5.f), glm::vec3(0.f, 10.f, 10.f))); 
	AddCollider(new Plane(glm::vec3(5.f, 10.f, -5.f), glm::vec3(10.f, 0.f, 10.f))); 
	AddCollider(new Plane(glm::vec3(-5.f, 0.f, -5.f), glm::vec3(0.f, 10.f, 10.f)));
	AddCollider(new Plane(glm::vec3(-5.f, 10.f, -5.f), glm::vec3(10.f, 10.f, 0.f)));
	AddCollider(new Plane(glm::vec3(5.f, 10.f, 5.f), glm::vec3(10.f, 10.f, 0.f)));
	
	_colliderSystem.SetSphere(sphere);
	_colliderSystem.SetCapsule(capsule);	
}

ParticleSim::~ParticleSim() {
	for (int i = 0; i < particleSystems.size(); i++) {
		delete particleSystems[i];
	}
}

void ParticleSim::Update(float dt) {
	for (int i = 0; i < particleSystems.size(); i++) {
		particleSystems[i]->Update(dt, _colliders);
	}
}

void ParticleSim::RenderUpdate() {
	for (int i = 0; i < particleSystems.size(); i++) {
		particleSystems[i]->Render();
	}
	_colliderSystem.Render();
}

void ParticleSim::RenderGui() {
	ImGui::SliderFloat("Fountain Emission Rate (particles/s)", &particleSystems[0]->emissionRate, MIN_EMISSION_RATE, MAX_EMISSION_RATE);

	ImGui::SliderFloat("Cascade Emission Rate (particles/s)", &particleSystems[1]->emissionRate, MIN_EMISSION_RATE, MAX_EMISSION_RATE);

	ImGui::SliderFloat("Sphere X Position", &_colliderSystem.GetSphere()->_coordinates.x, MIN_X_POSITION, MAX_X_POSITION);
	ImGui::SliderFloat("Sphere Y Position", &_colliderSystem.GetSphere()->_coordinates.y, MIN_Y_POSITION, MAX_Y_POSITION);
	ImGui::SliderFloat("Sphere Z Position", &_colliderSystem.GetSphere()->_coordinates.z, MIN_Z_POSITION, MAX_Z_POSITION);
	ImGui::SliderFloat("Sphere Radius", &_colliderSystem.GetSphere()->_radius, MIN_RADIUS, MAX_RADIUS);

	ImGui::SliderFloat("Capsule X Position A", &_colliderSystem.GetCapsule()->_pointACoordinates.x, MIN_X_POSITION, MAX_X_POSITION);
	ImGui::SliderFloat("Capsule Y Position A", &_colliderSystem.GetCapsule()->_pointACoordinates.y, MIN_Y_POSITION, MAX_Y_POSITION);
	ImGui::SliderFloat("Capsule Z Position A", &_colliderSystem.GetCapsule()->_pointACoordinates.z, MIN_Z_POSITION, MAX_Z_POSITION);
	ImGui::SliderFloat("Capsule X Position B", &_colliderSystem.GetCapsule()->_pointBCoordinates.x, MIN_X_POSITION, MAX_X_POSITION);
	ImGui::SliderFloat("Capsule Y Position B", &_colliderSystem.GetCapsule()->_pointBCoordinates.y, MIN_Y_POSITION, MAX_Y_POSITION);
	ImGui::SliderFloat("Capsule Z Position B", &_colliderSystem.GetCapsule()->_pointBCoordinates.z, MIN_Z_POSITION, MAX_Z_POSITION);
	ImGui::SliderFloat("Capsule Radius", &_colliderSystem.GetCapsule()->_radius, MIN_RADIUS, MAX_RADIUS);
}

