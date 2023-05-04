#include "RigidBody.h"

RigidBody::RigidBody(glm::vec3 initialForce) : _force(initialForce)
{
	srand(time(NULL));

	_cube = manager.NewCube(glm::mat4(1.f));

	_positionMatrix = CalculatePosition(glm::vec3(-5 + (rand() % 10), rand() % 10, -5 + (rand() % 10)));

	_rotationQuaternion = RotationMatrixWithQuaternions(rand() % 360, glm::vec3(rand() % 1000, rand() % 1000, rand() % 1000));

	//_cube->Update(_positionMatrix * glm::mat4(_rotationQuaternion));
}

RigidBody::~RigidBody()
{
	manager.DestroyPrimitive(_cube);
}

void RigidBody::Update(float dt)
{
	_positionMatrix = CalculatePosition(glm::vec3(sinf(ImGui::GetTime()) * 5.f, 5.f + cosf(ImGui::GetTime()) * 5.f, 0.f));

	_rotationQuaternion *= RotationMatrixWithQuaternions(glm::radians(float((int)ImGui::GetTime() % 360)), glm::vec3(5, 2, -3.f));

	_cube->Update(_positionMatrix * glm::mat4(_rotationQuaternion));
}

glm::mat4 RigidBody::CalculatePosition(glm::vec3 position)
{
	return glm::translate(glm::mat4(), position);
}

glm::quat RigidBody::RotationMatrixWithQuaternions(float rotation, glm::vec3 direction)
{
	return glm::quat(cosf(rotation / 2), glm::normalize(direction) * sinf(rotation / 2));
}