
#pragma once
#include <vector>

#include "ColliderSystem.h"
#include "Plane.h"
#include "Spring.h"
#include "VerletFrame.h"

class FluidNode
{

public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 force;

    FluidNode(glm::vec3 position);
    ~FluidNode();

    void ResetForce();

    void CalculateTotalForce();

    glm::vec3 UpdatePosition(std::vector<Collider*> colliders, float dt);

    Plane* CheckColliders(glm::vec3 nextPosition, std::vector<Collider*> colliders) const;
    Plane* CalculateSpherePlane(glm::vec3 nextPosition, Collider* collider) const;
    void PositionAfterCollision(glm::vec3 nextPosition, glm::vec3 normal, float d);
    void VelocityAfterCollision(glm::vec3 nextVelocity, glm::vec3 normal);

};