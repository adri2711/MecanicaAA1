#include "RigidBodySystem.h"

RigidBodySystem::RigidBodySystem()
{
	_initialForce = glm::normalize(glm::vec3(3.f, 2.f, -3.f));
	_rigidBody = new RigidBody(_initialForce);
}

RigidBodySystem::~RigidBodySystem()
{
	delete _rigidBody;
}

void RigidBodySystem::UpdateRigidBody(float dt)
{
	_rigidBody->Update(dt);
}
