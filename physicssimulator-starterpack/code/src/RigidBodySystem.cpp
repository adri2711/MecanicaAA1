#include "RigidBodySystem.h"

RigidBodySystem::RigidBodySystem()
{
	_initialForce = glm::normalize(glm::vec3(3.f, 2.f, -3.f));
}

RigidBodySystem::~RigidBodySystem()
{
}

void RigidBodySystem::UpdateRigidBody(float dt)
{
	_rigidBody->Update(dt);
}
