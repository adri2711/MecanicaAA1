#include "RigidBody.h"

RigidBody::RigidBody(float initialRotation, glm::vec3 initialDirection, glm::vec3 centerOfMass, float mass,
	glm::vec3 linearVelocity, glm::vec3 angularVelocity, glm::mat3 iBody, std::vector<glm::vec3> particlesLocalPosition) :
	_mass(mass), _iBody(iBody), _particlesLocalPosition(particlesLocalPosition)
{
	for (int i = 0; i < _particlesLocalPosition.size(); ++i)
	{
		_particlesWorldPosition.push_back(glm::vec3());
	}

	_state.rotationQuaternion = CalculateRotationQuaternion(initialRotation, initialDirection);
	_state.positionMatrix = CalculatePositionMatrix(centerOfMass);
	_state.linearMomentum = glm::vec3(0);
	_state.angularMomentum = glm::vec3(0);
}

RigidBody::~RigidBody()
{
	
}

glm::mat4 RigidBody::CalculatePositionMatrix(glm::vec3 position)
{	
	_centerOfMass = position;

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

glm::mat3 RigidBody::CalculateInertialTensorMatrix() const
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

glm::vec3 RigidBody::CalculateParticlesPosition(glm::vec3 position) const
{
	return _state.rotationQuaternion * position + _centerOfMass;
}

glm::vec3 RigidBody::CalculateLinearVelocity(float dt) const
{
	return glm::vec3();
}

glm::vec3 RigidBody::CalculateLinearMomentum() const
{
	//return _mass * _state.linearVelocity;
	return glm::vec3();
}

glm::vec3 RigidBody::CalculateAngularVelocity() const
{
	return glm::vec3();
}

glm::vec3 RigidBody::CalculateAngularMomentum(glm::mat3 iBody) const
{
	//return iBody * _state.angularVelocity;
	return glm::vec3();
}

glm::vec3 RigidBody::CalculateTorque() const
{
	glm::vec3 auxVector = glm::vec3(0);

	for (int i = 0; i < _particlesLocalPosition.size(); ++i)
	{
		//auxVector += glm::cross(_particlesLocalPosition[i], _state.linearVelocity);
	}

	return auxVector;
}

glm::mat3 RigidBody::QuaternionToMatrix(glm::quat quaternion) const
{
	return 2.f * glm::mat3(
	
		glm::vec3(0.5f - pow(quaternion.y, 2.f) - pow(quaternion.z, 2.f), quaternion.x * quaternion.y + quaternion.w * quaternion.z, quaternion.x * quaternion.z - quaternion.w * quaternion.y),
		glm::vec3(quaternion.x * quaternion.y - quaternion.w * quaternion.z, 0.5f - pow(quaternion.x ,2.f) - pow(quaternion.z, 2.f), quaternion.y * quaternion.z + quaternion.w * quaternion.x),
		glm::vec3(quaternion.x * quaternion.z + quaternion.w * quaternion.y, quaternion.y * quaternion.z - quaternion.w * quaternion.x, 0.5f - pow(quaternion.x, 2.f) - pow(quaternion.y, 2.f))
	);
}

RigidBodyState RigidBody::SemiImplicitEuler() const
{
	return RigidBodyState();
}
