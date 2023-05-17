#pragma once

#include "Cube.h"

class RigidBodySystem
{
private:

	Cube* _rigidBody;

public:

	RigidBodySystem();
	~RigidBodySystem();

	void UpdateRigidBody(float dt);
};