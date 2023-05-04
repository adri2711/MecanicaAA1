#include "RigidbodySim.h"

#include <iostream>
#include<glm/gtx/string_cast.hpp>

RigidBodySim::RigidBodySim()
{
	
}

RigidBodySim::~RigidBodySim()
{	
	manager.DestroyPrimitive(_cube);
	delete _rigidBodySystem;
	delete _colliderSystem;
}

void RigidBodySim::Update(float dt)
{
	_angularVelocity = glm::vec3(0.f, 1.f, 0.f) * 5.f;

	_angularVelocityMatrix = glm::mat3(

		glm::vec3(0.f, -_angularVelocity.x, _angularVelocity.y),
		glm::vec3(_angularVelocity.z, 0, -_angularVelocity.x),
		glm::vec3(-_angularVelocity.y, _angularVelocity.x, 0)

	);

	_rotationMatrix += dt * (_angularVelocityMatrix * _rotationMatrix);

	//std::cout << glm::to_string(_rotationMatrix) << std::endl;
}

void RigidBodySim::RenderUpdate()
{
	_cube->Update(_rotationMatrix);
}

void RigidBodySim::RenderGui()
{
}