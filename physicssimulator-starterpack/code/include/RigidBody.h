#pragma once

#include <glm/glm.hpp>

class RigidBody
{
private:

    graphics::CubePrimitive* _cube;
    glm::mat3 _rotationMatrix;
    glm::mat3 _angularVelocityMatrix;

    glm::vec3 _angularVelocity;

    float roll = 0.f;
    float pitch = 0.f;
    float yaw = 0.f;

public:

	RigidBody();
	~RigidBody();

    void UpdatePosition();

};

