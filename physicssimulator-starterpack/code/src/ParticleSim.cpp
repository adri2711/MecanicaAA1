#include <ParticleSim.h>
#include <imgui/imgui.h>
#include "FountainParticleSystem.h"

ParticleSim::ParticleSim() {
	particleSystems.push_back(new FountainParticleSystem());
	particleSystems[0]->position = glm::vec3(2, 4, 0);
	particleSystems[0]->emissionRate = 2.f;
	particleSystems[0]->particleLifeTime = 2.f;
	static_cast<FountainParticleSystem*>(particleSystems[0])->angle = 40.f;
	static_cast<FountainParticleSystem*>(particleSystems[0])->velocityMagnitude = 7.f;
	static_cast<FountainParticleSystem*>(particleSystems[0])->coneDir = glm::vec3(0.f, 1.0f, 0.f);
	particleSystems[0]->Setup();
}

ParticleSim::~ParticleSim() {
	for (int i = 0; i < particleSystems.size(); i++) {
		delete particleSystems[i];
	}
}

void ParticleSim::Update(float dt) {
	for (int i = 0; i < particleSystems.size(); i++) {
		particleSystems[i]->Update(dt);
	}
}

void ParticleSim::RenderUpdate() {
	for (int i = 0; i < particleSystems.size(); i++) {
		particleSystems[i]->Render();
	}
}

void ParticleSim::RenderGui() {
	ImGui::SliderFloat("Emissin Rate (particles/s)", &particles->emissionRate, ParticleSystem::MIN)
}

