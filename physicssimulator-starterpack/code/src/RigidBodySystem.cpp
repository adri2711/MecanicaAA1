#include "RigidBodySystem.h"

#include "Cube.h"

RigidBodySystem::RigidBodySystem()
{
	glm::vec3 centerOfMass = glm::vec3(-4 + (rand() % 8), rand() % 10, -4 + (rand() % 8));

	glm::vec3 initialDirection = glm::vec3(rand() % 1000, rand() % 1000, rand() % 1000);

	float initialRotation = rand() % 360;

	float mass = 1;
	
	glm::vec3 linearVelocity = glm::normalize(glm::vec3(3.f, 2.f, -3.f));

	std::vector<glm::vec3> particlesLocalPosition;	

	particlesLocalPosition.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	particlesLocalPosition.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	particlesLocalPosition.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	particlesLocalPosition.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	
	_rigidBody = new Cube(initialRotation, initialDirection, centerOfMass, mass, linearVelocity, particlesLocalPosition);
}

RigidBodySystem::~RigidBodySystem()
{
	delete _rigidBody;
}

void RigidBodySystem::UpdateRigidBody(float dt)
{
	_rigidBody->Update(dt);
}
