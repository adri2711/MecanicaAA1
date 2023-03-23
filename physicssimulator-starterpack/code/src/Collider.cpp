#include "Collider.h"

Collider::Collider()
{
	_active = true;
	_colliderType = PLANE;
}

Collider::Collider(bool activate, ColliderType colliderType) : _active{activate},
	_colliderType{colliderType}
{	
}

Collider::~Collider()
{	
}

void Collider::SetActive(bool active)
{
	_active = active;
}

bool Collider::GetActive()
{
	return _active;
}

void Collider::SetNormal(glm::vec3 normal)
{
	_normal = normal;
}

glm::vec3 Collider::GetNormal()
{
	return _normal;
}

void Collider::SetD(float d)
{
	_d = d;
}

float Collider::GetD()
{
	return _d;
}


ColliderType Collider::GetColliderType()
{
	return _colliderType;
}