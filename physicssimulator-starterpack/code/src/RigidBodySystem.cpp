#include "RigidBodySystem.h"

#include "Cube.h"
#include <iostream>

RigidBodySystem::RigidBodySystem()
{
	//glm::vec3 centerOfMass = glm::vec3(-4 + (rand() % 8), rand() % 10, -4 + (rand() % 8));
	glm::vec3 centerOfMass = glm::vec3(0.f, 3.f, 0.f);

	glm::vec3 initialDirection = glm::vec3(rand() % 1000, rand() % 1000, rand() % 1000);

	float initialRotation = rand() % 360;

	float mass = 0.1f;
	
	glm::vec3 linearVelocity = glm::normalize(glm::vec3(3.f, 2.f, -3.f));

	glm::vec3 angularVelocity = glm::vec3(3.f, 2.f, -3.f);

	std::vector<glm::vec3> particlesLocalPosition;	

	particlesLocalPosition.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	particlesLocalPosition.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	particlesLocalPosition.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	particlesLocalPosition.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	particlesLocalPosition.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	
	_rigidBody = new Cube(initialRotation, initialDirection, centerOfMass, glm::vec3(1.f, 1.f, 1.f), mass, linearVelocity, angularVelocity, particlesLocalPosition);

	_rigidBody->AddForce(Force(POINT, glm::vec3(30.f, 30.f, 0.f), glm::vec3(centerOfMass + glm::vec3(0.f, -0.5f, 0.f))));
}

RigidBodySystem::~RigidBodySystem()
{
	delete _rigidBody;
}

void RigidBodySystem::UpdateRigidBody(float dt)
{
	// Gravity
	_rigidBody->AddForce(Force(GLOBAL, glm::vec3(0.f, -9.8f * _rigidBody->_mass, 0.f), glm::vec3()));

	//if (int(ImGui::GetTime() * 10.f) % 10 == 9) {
	//	_rigidBody->AddForce(Force(POINT, glm::vec3(0.f, 220.f, 0.f), glm::vec3()));
	//}

	_rigidBody->Update(dt);
}
