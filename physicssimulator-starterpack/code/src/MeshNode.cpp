#include "MeshNode.h"

MeshNode::MeshNode(glm::vec3 position) : _position(position)
{
    _verletFrame = VerletFrame(_position, _position);
}

MeshNode::~MeshNode()
{
    
}

void MeshNode::AddSpring(SpringType springType, float elasticity, float damping, float springLength, int connectPointIndex)
{
    _springs.push_back(Spring(springType, elasticity, damping, springLength, connectPointIndex));
}


glm::vec3 MeshNode::GetPosition()
{
    return  _position;
}

std::vector<Spring> MeshNode::GetSprings()
{
    return _springs;
}

void MeshNode::UpdatePosition(float dt)
{
    _position = _verletFrame.CalculateNextPosition(dt);
}
