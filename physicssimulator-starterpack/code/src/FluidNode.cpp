#include "FluidNode.h"

#include <iostream>

FluidNode::FluidNode(glm::vec3 position)
{
	this->position = position;
}

FluidNode::~FluidNode()
{
}

void FluidNode::ResetForce()
{
	force = glm::vec3(0.f, 0.f, 0.f);
}

void FluidNode::CalculateTotalForce()
{
}

glm::vec3 FluidNode::UpdatePosition(std::vector<Collider*> colliders, float dt)
{
	return position;
}

Plane* FluidNode::CheckColliders(glm::vec3 nextPosition, std::vector<Collider*> colliders) const
{
	return nullptr;
}

Plane* FluidNode::CalculateSpherePlane(glm::vec3 nextPosition, Collider* collider) const
{
	return nullptr;
}

void FluidNode::PositionAfterCollision(glm::vec3 nextPosition, glm::vec3 normal, float d)
{
}

void FluidNode::VelocityAfterCollision(glm::vec3 nextVelocity, glm::vec3 normal)
{
}
