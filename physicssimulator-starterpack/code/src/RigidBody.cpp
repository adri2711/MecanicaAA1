#include "RigidBody.h"

RigidBody::RigidBody()
{
	_cube = manager.NewCube(glm::mat4(1.f));

	// Build rotation Matrix
	glm::mat3 Rx = glm::mat3(

		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f, glm::cos(roll), -glm::sin(roll)),
		glm::vec3(0.f, glm::sin(roll), glm::cos(roll))
	);

	glm::mat3 Ry = glm::mat3(

		glm::vec3(glm::cos(pitch), 0.f, glm::sin(pitch)),
		glm::vec3(0, 1, 0),
		glm::vec3(-glm::sin(pitch), 0, glm::cos(pitch))
	);

	glm::mat3 Rz = glm::mat3(

		glm::vec3(glm::cos(yaw), -glm::sin(yaw), 0.f),
		glm::vec3(glm::sin(yaw), glm::cos(yaw), 0.f),
		glm::vec3(0.f, 0.f, 1.f)
	);

	_rotationMatrix = Rz * Ry * Rx;
}

RigidBody::~RigidBody()
{
}

void RigidBody::UpdatePosition()
{
	_angularVelocity = glm::vec3(0.f, 1.f, 0.f) * 5.f;

	_angularVelocityMatrix = glm::mat3(

		glm::vec3(0.f, -_angularVelocity.x, _angularVelocity.y),
		glm::vec3(_angularVelocity.z, 0, -_angularVelocity.x),
		glm::vec3(-_angularVelocity.y, _angularVelocity.x, 0)

	);

	_rotationMatrix += dt * (_angularVelocityMatrix * _rotationMatrix);
}
