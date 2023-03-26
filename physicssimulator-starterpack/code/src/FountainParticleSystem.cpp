#include "FountainParticleSystem.h"
#include <time.h>

void FountainParticleSystem::ParticleUpdate(int i, float dt, std::vector<Collider*> colliders)
{
	ParticleSystem::ParticleUpdate(i, dt, colliders);
}

Particle FountainParticleSystem::CreateParticle()
{
	float randYaw = rand() % 360;
	float randPitch = rand() % (int)angle;
	glm::mat4 yaw = glm::rotate(glm::mat4(), glm::radians(randYaw), dirNorm);
	glm::mat4 pitch = glm::rotate(glm::mat4(), glm::radians(randPitch), glm::normalize(glm::cross(dirNorm, glm::vec3(1.f,1.f,1.f))));
	glm::vec4 v0 = glm::vec4(coneDir, 0.f) * pitch * yaw * velocityMagnitude;

	return Particle(position, v0, gravity, particleLifeTime, particleMass);
}

void FountainParticleSystem::SetDirection(glm::vec3 dir) {
	coneDir = dir;
	dirNorm = glm::normalize(dir);
}

void FountainParticleSystem::Setup()
{
	srand(time(NULL));
	ParticleSystem::Setup();
}
