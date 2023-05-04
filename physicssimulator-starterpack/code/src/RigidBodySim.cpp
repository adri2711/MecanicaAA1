#include "RigidbodySim.h"

#include <iostream>
#include<glm/gtx/string_cast.hpp>

RigidBodySim::RigidBodySim()
{
	_rigidBodySystem = new RigidBodySystem();
	_colliderSystem = new ColliderSystem();
}

RigidBodySim::~RigidBodySim()
{	
	delete _rigidBodySystem;
	delete _colliderSystem;
}

void RigidBodySim::Update(float dt)
{
	_rigidBodySystem->UpdateRigidBody(dt);
}

void RigidBodySim::RenderUpdate()
{
	
}

void RigidBodySim::RenderGui()
{
}