#include "RigidBody.h"

RigidBody::RigidBody(glm::vec3 initialForce) : _force(initialForce)
{
	_cube = manager.NewCube(glm::mat4(1.f));



	_cube->Update(_positionMatrix * glm::mat4(_rotationQuaternion));
}

RigidBody::~RigidBody()
{
	manager.DestroyPrimitive(_cube);
}

void RigidBody::Update(float dt)
{
	_positionMatrix = glm::translate(glm::mat4(), glm::vec3(sinf(ImGui::GetTime()) * 5.f, 5.f + cosf(ImGui::GetTime()) * 5.f, 0.f));

	/*_rotationQuaternion *= RotationMatrixWithQuaternions(0.5f,
		glm::vec3(glm::vec3((glm::radians(float((int)ImGui::GetTime() % 360))) * dt,
			-(glm::radians(float((int)ImGui::GetTime() & 360))) * dt,
			-3.f)));*/

	_rotationQuaternion *= RotationMatrixWithQuaternions(glm::radians(float((int)ImGui::GetTime() % 360)), glm::vec3(5, 2, -3.f));

	_cube->Update(_positionMatrix * glm::mat4(_rotationQuaternion));
}

glm::mat4 RigidBody::CalculatePosition()
{
	
}

glm::quat RigidBody::RotationMatrixWithQuaternions(float rotation, glm::vec3 direction)
{
	return glm::quat(cosf(rotation / 2), glm::normalize(direction) * sinf(rotation / 2));
}