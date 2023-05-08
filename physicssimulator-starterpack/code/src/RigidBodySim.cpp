#include "RigidbodySim.h"

#include <iostream>
#include<glm/gtx/string_cast.hpp>

RigidBodySim::RigidBodySim()
{
	_reset = false;
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
	if (_reset)
	{
		delete _rigidBodySystem;
		_rigidBodySystem = new RigidBodySystem();
	}
	for (int i = 0; i < DT_DIVISOR; ++i)
	{
		_rigidBodySystem->UpdateRigidBody(dt / DT_DIVISOR);	
	}	
}

void RigidBodySim::RenderUpdate()
{
	
}

void RigidBodySim::RenderGui()
{
	_reset = ImGui::Button("Reset");
}