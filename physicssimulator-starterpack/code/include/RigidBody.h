#pragma once

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PrimitiveManager.h>
#include <ctime>

#include "Sphere.h"

extern graphics::PrimitiveManager manager;

class RigidBody
{
private:

    graphics::CubePrimitive* _cube;

    std::vector<graphics::SpherePrimitive*> _spheresPrimitive;

    std::vector<Sphere> _spheres;

    glm::mat4 _positionMatrix;

    glm::quat _rotationQuaternion;

    glm::mat3 _angularVelocityMatrix;
    glm::mat3 _inertialTensorMatrix;

    std::vector<glm::vec3> _particlesLocalPosition;
    std::vector<glm::vec3> _particlesWorldPosition;

    glm::vec3 _linearVelocity;
    glm::vec3 _angularVelocity;
    glm::vec3 _angularMomentum;
    glm::vec3 _lastPosition;
    glm::vec3 _centerOfMass;
    glm::vec3 _force;
    glm::vec3 _torque;

    float roll = 0.f;
    float pitch = 0.f;
    float yaw = 0.f;

public:

	RigidBody(glm::vec3 _initialForce);
	~RigidBody();

    void Update(float dt);
    glm::mat4 CalculatePosition(glm::vec3 position);
    glm::quat RotationMatrixWithQuaternions(float rotation, glm::vec3 direction);
    glm::mat3 CalculateInertialTensor();
    glm::vec3 CalculateParticlesPosition(glm::vec3 position);
    glm::vec3 CalculateLinearVelocity(float dt);
    glm::vec3 CalculateAngularVelocity();
    glm::vec3 CalculateTorque();

};

