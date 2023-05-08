#include "RigidBody.h"

#include <iostream>

RigidBody::RigidBody(glm::vec3 initialForce) : _force(initialForce)
{
	srand(time(NULL));

	_cube = manager.NewCube(glm::mat4(1.f));

	_particlesLocalPosition.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); 
	_particlesLocalPosition.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); 
	_particlesLocalPosition.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); 
	_particlesLocalPosition.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); 
	_particlesLocalPosition.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); 
	_particlesLocalPosition.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); 
	_particlesLocalPosition.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); 
	_particlesLocalPosition.push_back(glm::vec3(0.5f, 0.5f, -0.5f));

	_positionMatrix = CalculatePosition(glm::vec3(-4 + (rand() % 8), rand() % 10, -4 + (rand() % 8)));	

	_rotationQuaternion = RotationMatrixWithQuaternions(rand() % 360, glm::vec3(rand() % 1000, rand() % 1000, rand() % 1000));

	for (int i = 0; i < _particlesLocalPosition.size(); ++i)
	{
		_particlesWorldPosition.push_back(CalculateParticlesPosition(_particlesLocalPosition[i]));
	}

	for (int i = 0; i < _particlesWorldPosition.size(); ++i)
	{
		_spheres.push_back(Sphere(_particlesWorldPosition[i], 0.2f));
		_spheresPrimitive.push_back(manager.NewSphere(_spheres[i]._coordinates, _spheres[i]._radius));
	}

	_cube->Update(_positionMatrix * glm::mat4(_rotationQuaternion));
}

RigidBody::~RigidBody()
{
	manager.DestroyPrimitive(_cube);

	for (int i = 0; i < _spheresPrimitive.size(); ++i)
	{
		manager.DestroyPrimitive(_spheresPrimitive[i]);
	}
}

void RigidBody::Update(float dt)
{
	_positionMatrix = CalculatePosition(glm::vec3(sinf(ImGui::GetTime()) * 5.f, 5.f + cosf(ImGui::GetTime()) * 5.f, 0.f));

	_rotationQuaternion *= RotationMatrixWithQuaternions(glm::radians(float((int)ImGui::GetTime() % 360)), glm::vec3(5, 2, -3.f));

	_linearVelocity = CalculateLinearVelocity(dt);

	_angularVelocity = CalculateAngularVelocity();

	_inertialTensorMatrix = CalculateInertialTensor();

	_torque = CalculateTorque();

	for (int i = 0; i < _particlesWorldPosition.size(); ++i)
	{
		_particlesWorldPosition[i] = CalculateParticlesPosition(_particlesLocalPosition[i]);
	}
	
	for (int i = 0; i < _spheres.size(); ++i)
	{		
		_spheres[i]._coordinates = _particlesWorldPosition[i];
		_spheresPrimitive[i]->Update(_spheres[i]._coordinates, _spheres[i]._radius);
	}

	_cube->Update(_positionMatrix * glm::mat4(_rotationQuaternion));
}

glm::mat4 RigidBody::CalculatePosition(glm::vec3 position)
{
	_lastPosition = _centerOfMass;
	_centerOfMass = position;
	return glm::translate(glm::mat4(), position);
}

glm::quat RigidBody::RotationMatrixWithQuaternions(float rotation, glm::vec3 direction)
{
	return glm::quat(cosf(rotation / 2), glm::normalize(direction) * sinf(rotation / 2));
}

glm::mat3 RigidBody::CalculateInertialTensor()
{
	glm::mat3 auxInertialTensorMatrix = glm::mat3(0);

	
	for (int i = 0; i < _particlesLocalPosition.size(); ++i)
	{
		glm::mat3 auxMatrix = glm::mat3(

			glm::vec3(1 * (pow(_particlesLocalPosition[i].y, 2.f) + pow(_particlesLocalPosition[i].z, 2.f)),
				-1 * _particlesLocalPosition[i].x * _particlesLocalPosition[i].y,
				-1 * _particlesLocalPosition[i].x * _particlesLocalPosition[i].z),
				
			glm::vec3(-1 * _particlesLocalPosition[i].y * _particlesLocalPosition[i].x,
				1 * (pow(_particlesLocalPosition[i].x, 2.f) + pow(_particlesLocalPosition[i].z, 2.f)),
				-1 * _particlesLocalPosition[i].y * _particlesLocalPosition[i].z),
			
			glm::vec3(-1 * _particlesLocalPosition[i].z * _particlesLocalPosition[i].x,
				-1 * _particlesLocalPosition[i].z * _particlesLocalPosition[i].y,
				1 * (pow(_particlesLocalPosition[i].x, 2.f) + pow(_particlesLocalPosition[i].y, 2.f)))
		);

		auxInertialTensorMatrix += auxMatrix;
	}
	
	return auxInertialTensorMatrix;	
}

glm::vec3 RigidBody::CalculateParticlesPosition(glm::vec3 position)
{
	return _rotationQuaternion * position + _centerOfMass;
}

glm::vec3 RigidBody::CalculateLinearVelocity(float dt)
{
	return (_centerOfMass - _lastPosition) / dt;
}

glm::vec3 RigidBody::CalculateAngularVelocity()
{
	
}

glm::vec3 RigidBody::CalculateTorque()
{
	glm::vec3 auxVector = glm::vec3(0);

	for (int i = 0; i < _particlesLocalPosition.size(); ++i)
	{
		auxVector += glm::cross(_particlesLocalPosition[i], _force);
	}

	return auxVector;
}
