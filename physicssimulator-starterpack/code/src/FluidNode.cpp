#include "FluidNode.h"
#include <iostream>

FluidNode::FluidNode(glm::vec3 position)
{
	this->position = initPosition = position;
	t = 0;
}

FluidNode::~FluidNode()
{
}

glm::vec3 FluidNode::UpdatePosition(std::vector<Collider*> colliders, std::vector<Wave> &waves, float dt)
{
	t += dt;
	glm::vec3 positionSum;
	for (int i = 0; i < waves.size(); i++) {
		positionSum += waves[i].GetPositionAtTime(position, t);
	}
	position = initPosition - positionSum;
	position.y = initPosition.y + positionSum.y;
	//std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
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
