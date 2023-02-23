#include <ParticleSim.h>
#include <PrimitiveManager.h>

ParticleSim::ParticleSim() {
	particleSystem.position = glm::vec3(0, 4, 0);
	particleSystem.Setup(10);
}

ParticleSim::~ParticleSim() {
	
}

void ParticleSim::Update(float dt) {
	particleSystem.Update(dt);
}