#include "RigidBody.h"
#include <iostream>

RigidBody::RigidBody(float initialRotation, glm::vec3 initialDirection, glm::vec3 centerOfMass, float mass,
	glm::vec3 linearVelocity, glm::vec3 angularVelocity, glm::mat3 iBody, std::vector<glm::vec3> particlesLocalPosition) :
	_mass(mass), _iBody(iBody), _particlesLocalPosition(particlesLocalPosition)
{
	for (int i = 0; i < _particlesLocalPosition.size(); ++i)
	{
		_particlesWorldPosition.push_back(glm::vec3());
	}

	_centerOfMass = centerOfMass;
	_state.rotationQuaternion = CalculateRotationQuaternion(initialRotation, initialDirection);
	_state.positionMatrix = CalculatePositionMatrix(centerOfMass);
	_state.linearMomentum = glm::vec3(0);
	_state.angularMomentum = glm::vec3(0);
}

RigidBody::~RigidBody()
{
	
}

void RigidBody::Update(float dt)
{
	_state = SemiImplicitEuler(dt);
}

void RigidBody::AddForce(Force force)
{
	_forces.push_back(force);
}

glm::mat4 RigidBody::CalculatePositionMatrix(glm::vec3 position)
{	
	for (int i = 0; i < _particlesWorldPosition.size(); ++i)
	{
		_particlesWorldPosition[i] = CalculateParticlesPosition(_particlesLocalPosition[i]);
	}
	
	return glm::translate(glm::mat4(), position);
}

glm::quat RigidBody::CalculateRotationQuaternion(float rotation, glm::vec3 direction) const
{
	return glm::quat(cosf(rotation / 2), glm::normalize(direction) * sinf(rotation / 2));
}

glm::mat3 RigidBody::CalculateSomethingWeird() const
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

glm::mat3 RigidBody::CalculateInverseInertiaTensor() const
{
	glm::mat3 rotMatrix = QuaternionToMatrix(_state.rotationQuaternion);
	return rotMatrix * glm::inverse(_iBody) * glm::transpose(rotMatrix);
}

glm::vec3 RigidBody::CalculateParticlesPosition(glm::vec3 position) const
{
	return _state.rotationQuaternion * position + _centerOfMass;
}

glm::vec3 RigidBody::CalculateLinearVelocity(glm::vec3 linearMomentum) const
{
	return linearMomentum / _mass;
}

glm::vec3 RigidBody::UpdateLinearMomentum(float dt) const
{
	glm::vec3 force;
	for (int i = 0; i < _forces.size(); i++) {
		force += _forces[i].forceVector;
	}
	return _state.linearMomentum + force * dt;
}

glm::vec3 RigidBody::CalculateAngularVelocity(glm::vec3 angularMomentum) const
{
	//std::cout << angularMomentum.x << ", " << angularMomentum.y << ", " << angularMomentum.z << std::endl;
	return CalculateInverseInertiaTensor() * angularMomentum;
}

glm::vec3 RigidBody::UpdateAngularMomentum(float dt) const
{
	return _state.angularMomentum * CalculateTorque() * dt;
}

glm::vec3 RigidBody::CalculateTorque() const
{
	glm::vec3 torque;
	for (int i = 0; i < _forces.size(); i++) {
		if (_forces[i].forceType == POINT) {
			glm::vec3 r = _forces[i].forcePosition - _centerOfMass;
			torque += glm::cross(r, _forces[i].forceVector);
		}
	}
	return torque;
}

glm::mat3 RigidBody::QuaternionToMatrix(glm::quat quaternion) const
{
	return 2.f * glm::mat3(
	
		glm::vec3(0.5f - pow(quaternion.y, 2.f) - pow(quaternion.z, 2.f), quaternion.x * quaternion.y + quaternion.w * quaternion.z, quaternion.x * quaternion.z - quaternion.w * quaternion.y),
		glm::vec3(quaternion.x * quaternion.y - quaternion.w * quaternion.z, 0.5f - pow(quaternion.x ,2.f) - pow(quaternion.z, 2.f), quaternion.y * quaternion.z + quaternion.w * quaternion.x),
		glm::vec3(quaternion.x * quaternion.z + quaternion.w * quaternion.y, quaternion.y * quaternion.z - quaternion.w * quaternion.x, 0.5f - pow(quaternion.x, 2.f) - pow(quaternion.y, 2.f))
	);
}

glm::vec3 RigidBody::UpdatePosition(glm::vec3 x0, glm::vec3 v, float dt)
{
	return x0 + v * dt;
}

glm::quat RigidBody::UpdateRotation(glm::quat r0, glm::vec3 w, float dt)
{
	//std::cout << w.x << ", " << w.y << ", " << w.z << std::endl;
	return 0.5f * w * r0;
}

RigidBodyState RigidBody::SemiImplicitEuler(float dt)
{
	RigidBodyState newState;
	newState.linearMomentum = UpdateLinearMomentum(dt);
	newState.angularMomentum = UpdateAngularMomentum(dt);
	_forces.clear();

	_centerOfMass = UpdatePosition(_centerOfMass, CalculateLinearVelocity(newState.linearMomentum), dt);
	newState.positionMatrix = CalculatePositionMatrix(_centerOfMass);
	newState.rotationQuaternion = UpdateRotation(_state.rotationQuaternion, CalculateAngularVelocity(newState.angularMomentum), dt);
	return newState;
}
