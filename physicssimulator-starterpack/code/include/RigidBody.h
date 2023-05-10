#pragma once

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PrimitiveManager.h>
#include <ctime>

#include "Sphere.h"

extern graphics::PrimitiveManager manager;

struct RigidBodyState
{    
    glm::quat rotationQuaternion;
    
    glm::mat4 positionMatrix;

    glm::vec3 linearMomentum;
    glm::vec3 angularMomentum;
};

class RigidBody
{
protected:

    RigidBodyState _state;
    
    std::vector<glm::vec3> _particlesLocalPosition;
    std::vector<glm::vec3> _particlesWorldPosition;

    glm::mat3 _iBody;

    glm::vec3 _centerOfMass;

    float _mass;

    float roll = 0.f;
    float pitch = 0.f;
    float yaw = 0.f;
    
    glm::mat4 CalculatePositionMatrix(glm::vec3 position);
    glm::quat CalculateRotationQuaternion(float rotation, glm::vec3 direction) const;
    glm::mat3 CalculateInertialTensorMatrix() const;
    glm::vec3 CalculateParticlesPosition(glm::vec3 position) const;
    glm::vec3 CalculateLinearVelocity(float dt) const;
    glm::vec3 CalculateLinearMomentum() const;
    glm::vec3 CalculateAngularVelocity() const;
    glm::vec3 CalculateAngularMomentum(glm::mat3 iBody) const;
    glm::vec3 CalculateTorque() const;
    glm::mat3 QuaternionToMatrix(glm::quat quaternion) const;
    RigidBodyState SemiImplicitEuler() const;


public:

	RigidBody(float initialRotation, glm::vec3 initialDirection, glm::vec3 centerOfMass, float mass,
	    glm::vec3 linearVelocity, glm::vec3 angularVelocity, glm::mat3 iBody,
	    std::vector<glm::vec3> particlesLocalPosition);
	virtual ~RigidBody() = 0;

    virtual void Update(float dt) = 0;

};

struct CollisionState
{
    RigidBody* vertex;
    RigidBody* faces;

    glm::vec3 contactPoint;
    glm::vec3 faceNormal;
    
    bool hasCollided;
    bool inContact;

    float distanceToContact;    
};