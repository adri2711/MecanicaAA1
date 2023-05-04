#pragma once

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PrimitiveManager.h>
#include <ctime>

extern graphics::PrimitiveManager manager;

class RigidBody
{
private:

    graphics::CubePrimitive* _cube;
    glm::mat4 _positionMatrix;
    glm::quat _rotationQuaternion;
    glm::mat3 _angularVelocityMatrix;

    glm::vec3 _angularVelocity;

    glm::vec3 _position;
    glm::vec3 _force;

    float roll = 0.f;
    float pitch = 0.f;
    float yaw = 0.f;

public:

	RigidBody(glm::vec3 _initialForce);
	~RigidBody();

    void Update(float dt);
    glm::mat4 CalculatePosition(glm::vec3 position);
    glm::quat RotationMatrixWithQuaternions(float rotation, glm::vec3 direction);

};

