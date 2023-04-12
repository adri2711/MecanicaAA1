#pragma once
#include <vector>

#include "ColliderSystem.h"
#include "Plane.h"
#include "Spring.h"
#include "VerletFrame.h"

class MeshNode
{
private:
    
    glm::vec3* _position;
    glm::vec3* _velocity;
    glm::vec3* _force;
    VerletFrame _verletFrame;
    std::vector<Spring> _springs;
    
public:

    MeshNode(glm::vec3 position);
    ~MeshNode();

    void AddSpring(SpringType springType, float elasticity, float damping, float springLength, int connectPointIndex,
        glm::vec3** connectedMeshNodePosition, glm::vec3** connectedMeshNodeVelocity, glm::vec3** connectedMeshNodeAcceleration);
    
    glm::vec3** GetPosition();
    glm::vec3** GetVelocity();
    glm::vec3** GetForce();

    void ShowForce();

    std::vector<Spring> GetSprings();

    void CalculateTotalForce();

    glm::vec3* UpdatePosition(std::vector<Collider*> colliders,float dt);

    Plane* CheckColliders(glm::vec3 nextPosition, std::vector<Collider*> colliders) const;
    Plane* CalculateSpherePlane(glm::vec3 nextPosition, Collider* collider) const;
    void PositionAfterCollision(glm::vec3 nextPosition, glm::vec3 normal, float d);
    void VelocityAfterCollision(glm::vec3 nextVelocity, glm::vec3 normal);
    
};
