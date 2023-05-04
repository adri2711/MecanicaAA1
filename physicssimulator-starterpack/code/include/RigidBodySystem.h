#pragma once

#include "RigidBody.h"

class RigidBodySystem
{
private:

	RigidBody* _rigidBody;

	glm::vec3 _initialForce;

public:

	RigidBodySystem();
	~RigidBodySystem();

	void UpdateRigidBody(float dt);
};