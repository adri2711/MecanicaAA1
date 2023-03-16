#include <ParticleSim.h>
#include <imgui/imgui.h>
#include "FountainParticleSystem.h"
#include "CascadeParticleSystem.h"
#include "Plane.h"

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
	
	AddCollider(new Plane(glm::vec3(-5.f, 0.f, -5.f), glm::vec3(10.f, 0.f, 10.f)));
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
}

void ParticleSim::RenderGui() {
	//ImGui::SliderFloat("Emissin Rate (particles/s)", &particles->emissionRate, ParticleSystem::MIN)
}

