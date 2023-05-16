#pragma once

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PrimitiveManager.h>
#include <ctime>
#include <vector>

#include "Sphere.h"

extern graphics::PrimitiveManager manager;

struct RigidBodyState
{    
    glm::quat rotationQuaternion;
    
    glm::mat4 positionMatrix;

    glm::vec3 linearMomentum;
    glm::vec3 angularMomentum;
};

enum ForceType { POINT, GLOBAL };
struct Force
{
    ForceType forceType;
    glm::vec3 forceVector;
    glm::vec3 forcePosition;
    Force(ForceType forceType, glm::vec3 forceVector, glm::vec3 forcePosition)
        : forceType(forceType), forceVector(forceVector),  forcePosition(forcePosition) {}
};

class RigidBody
{
public:

    RigidBodyState _state;

    std::vector<glm::vec3> _particlesLocalPosition;
    std::vector<glm::vec3> _particlesWorldPosition;

    glm::mat3 _iBody;

    glm::vec3 _centerOfMass;

    std::vector<Force> _forces;

    float _mass;

    float roll = 0.f;
    float pitch = 0.f;
    float yaw = 0.f;

protected:
    
    virtual glm::mat4 CalculatePositionMatrix(glm::vec3 position);
    virtual glm::quat CalculateRotationQuaternion(float rotation, glm::vec3 direction) const;
    virtual glm::mat3 CalculateSomethingWeird() const;
    virtual glm::mat3 CalculateInverseInertiaTensor() const;
    virtual glm::vec3 CalculateParticlesPosition(glm::vec3 position) const;
    virtual glm::vec3 CalculateLinearVelocity(glm::vec3 linearMomentum) const;
    virtual glm::vec3 UpdateLinearMomentum(float dt) const;
    virtual glm::vec3 CalculateAngularVelocity(glm::vec3 angularMomentum) const;
    virtual glm::vec3 UpdateAngularMomentum(float dt) const;
    virtual glm::vec3 CalculateTorque() const;
    virtual glm::mat3 QuaternionToMatrix(glm::quat quaternion) const;
    virtual glm::vec3 UpdatePosition(glm::vec3 x0, glm::vec3 v, float dt);
    virtual glm::quat UpdateRotation(glm::quat r0, glm::vec3 w, float dt);
    RigidBodyState SemiImplicitEuler(float dt);


public:

	RigidBody(float initialRotation, glm::vec3 initialDirection, glm::vec3 centerOfMass, float mass,
	    glm::vec3 linearVelocity, glm::vec3 angularVelocity, glm::mat3 iBody,
	    std::vector<glm::vec3> particlesLocalPosition);
	virtual ~RigidBody();

    virtual void Update(float dt);
    virtual void AddForce(Force force);

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