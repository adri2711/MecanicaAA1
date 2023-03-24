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

ColliderType Collider::GetColliderType()
{
	return _colliderType;
}