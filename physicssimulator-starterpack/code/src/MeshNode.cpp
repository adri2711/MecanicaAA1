#include "MeshNode.h"

#include <iostream>

MeshNode::MeshNode(glm::vec3 position) : _position(new glm::vec3(position)), _velocity(new glm::vec3()), _force(new glm::vec3())
{
    _verletFrame = VerletFrame(*_position, *_position);
}

MeshNode::~MeshNode()
{
    for (int i = 0; i < _springs.size(); ++i)
    {
        delete _springs[i].GetConnectedMeshPosition();
    }
}

void MeshNode::AddSpring(SpringType springType, float elasticity, float damping, float springLength, int connectPointIndex,
	glm::vec3* connectedMeshNodePosition, glm::vec3* connectedMeshNodeVelocity, glm::vec3* connectedMeshNodeForce)
{
    _springs.push_back(Spring(springType, elasticity, damping, springLength, connectPointIndex,
    	connectedMeshNodePosition, connectedMeshNodeVelocity, connectedMeshNodeForce));
}


glm::vec3* MeshNode::GetPosition()
{
    return _position;
}

glm::vec3* MeshNode::GetVelocity()
{
	return _velocity;
}

glm::vec3* MeshNode::GetForce()
{
	return _force;
}

void MeshNode::ResetForce()
{
	*_force = glm::vec3(0,0,0);
}

std::vector<Spring> MeshNode::GetSprings()
{
    return _springs;
}

void MeshNode::CalculateTotalForce()
{
    glm::vec3 auxTotalForce = glm::vec3();
    
    for (int i = 0; i < _springs.size(); ++i)
    {
        auxTotalForce += _springs[i].CalculateForce(*_position, *_velocity);
    }
    
    *_force += auxTotalForce;
}

glm::vec3* MeshNode::UpdatePosition(std::vector<Collider*> colliders, float dt)
{	
    CalculateTotalForce();
    glm::vec3 nextPosition = _verletFrame.CalculateNextPosition(*_position, *_force, dt);	
	*_velocity = _verletFrame.CalculateNextVelocity(dt);
	
	Plane* plane = CheckColliders(nextPosition, colliders);
    if (plane != nullptr)
    {
	    PositionAfterCollision(nextPosition, plane->GetNormal(), plane->GetD());
    	_verletFrame.SetNextPosition(*_position);
    	VelocityAfterCollision(*_velocity, plane->GetNormal());
    }
    else
    {
    	*_position = nextPosition;
    }

    return _position;    
}

Plane* MeshNode::CheckColliders(glm::vec3 nextPosition, std::vector<Collider*> colliders) const
{
	for (int j = 0; j < colliders.size(); j++)
	{
		Collider* collider = colliders[j];

		if (collider->GetColliderType() == PLANE)
		{
			Plane* plane = reinterpret_cast<Plane*>(collider);
			float d = plane->GetD();
			glm::vec3 normal = plane->GetNormal();			

			if ((glm::dot(normal, *_position) + d) * (glm::dot(normal, nextPosition) + d) <= 0.f)
			{
				return plane;				
			}			
		}
		else if (collider->GetColliderType() == SPHERE)
		{
			Plane* plane = CalculateSpherePlane(nextPosition, collider);

			if (plane != nullptr)
			{
				return plane;
			}
			
		}
	}
	return nullptr;
}


Plane* MeshNode::CalculateSpherePlane(glm::vec3 nextPosition, Collider* collider) const
{
	Sphere* sphere = reinterpret_cast<Sphere*>(collider);
			
	glm::vec3 vectorToSphereCenter = sphere->_coordinates - nextPosition;
			
	if (sqrt(glm::dot(vectorToSphereCenter, vectorToSphereCenter)) <= sphere->_radius)
	{		
		glm::vec3 vectorBetweenPositions = nextPosition - *_position;
				
		float a = sphere->CalculateA(*_position);
		float b = sphere->CalculateB(*_position, vectorBetweenPositions);
		float c = sphere->CalculateC(vectorBetweenPositions);
		float d = a + b + c;

		float result1 = (-b + sqrt(pow(b,2) - 4 * a * (c - d))) / 2 * a;
		float result2 = (-b - sqrt(pow(b,2) - 4 * a * (c - d))) / 2 * a;

		float alpha = fminf(result1, result2);

		glm::vec3 collisionPoint = *_position + vectorBetweenPositions * alpha;

		Plane* plane = new Plane(collisionPoint);
		plane->SetNormal(collisionPoint - sphere->_coordinates);
		plane->CalculateD();

		return plane;				
	}

	return nullptr;
}

void MeshNode::PositionAfterCollision(glm::vec3 nextPosition, glm::vec3 normal, float d) {
	
	*_position = nextPosition - 2.f * ((glm::dot(normal, nextPosition) + d) * normal);	
}

void MeshNode::VelocityAfterCollision(glm::vec3 nextVelocity, glm::vec3 normal) {
		
	*_velocity = nextVelocity - 2.f * (glm::dot(normal, nextVelocity) * normal);
}