#include "MeshNode.h"

#include <iostream>

MeshNode::MeshNode(glm::vec3 position) : _position(new glm::vec3(position))
{
    _verletFrame = VerletFrame(position, position);
}

MeshNode::~MeshNode()
{
    
}

void MeshNode::AddSpring(SpringType springType, float elasticity, float damping, float springLength, int connectPointIndex, glm::vec3** connectedMeshNodePosition)
{
    _springs.push_back(Spring(springType, elasticity, damping, springLength, connectPointIndex, connectedMeshNodePosition));
}


glm::vec3** MeshNode::GetPosition()
{
    return &_position;
}

std::vector<Spring> MeshNode::GetSprings()
{
    return _springs;
}

void MeshNode::CalculateTotalForce()
{
       
}

float MeshNode::GetTotalForce()
{
    return _totalForce;
}

glm::vec3* MeshNode::UpdatePosition(float dt)
{
    _position = _verletFrame.CalculateNextPosition(dt);
    return _position;
}
