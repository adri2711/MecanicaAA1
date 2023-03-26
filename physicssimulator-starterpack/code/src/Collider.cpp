#include "Collider.h"

Collider::Collider()
{
	_colliderType = PLANE;
}

Collider::Collider(bool activate, ColliderType colliderType) : _colliderType{colliderType}
{	
}

Collider::~Collider()
{
}

ColliderType Collider::GetColliderType()
{
	return _colliderType;
}