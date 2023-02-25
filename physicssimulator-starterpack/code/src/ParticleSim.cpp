#include <ParticleSim.h>
#include "FountainParticleSystem.h"

ParticleSim::ParticleSim() {
	particleSystem = new FountainParticleSystem();
	particleSystem->position = glm::vec3(0, 4, 0);
	particleSystem->emissionFrequency = 1.f;
	particleSystem->particleLifeTime = 2.f;
	static_cast<FountainParticleSystem*>(particleSystem)->angle = 30.f;
	static_cast<FountainParticleSystem*>(particleSystem)->velocityMagnitude = 5.f;
	static_cast<FountainParticleSystem*>(particleSystem)->coneDir = glm::vec3(cos(glm::radians(30.f)), sin(glm::radians(30.f)), 0.f);
	particleSystem->Setup();
}

ParticleSim::~ParticleSim() {
	delete particleSystem;
}

void ParticleSim::Update(float dt) {
	particleSystem->Update(dt);
}

void ParticleSim::RenderUpdate() {
	particleSystem->Render();
}

void ParticleSim::RenderGui() {

}

