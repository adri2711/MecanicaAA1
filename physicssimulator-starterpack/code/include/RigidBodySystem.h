#pragma once

#include "RigidBody.h"

class RigidBodySystem
{
private:

	RigidBody* _rigidBody;

public:

	RigidBodySystem();
	~RigidBodySystem();

	void UpdateRigidBody(float dt);
};