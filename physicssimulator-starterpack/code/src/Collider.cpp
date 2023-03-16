#include "Collider.h"

Collider::Collider()
{
	_active = true;
}

Collider::Collider(bool activate) : _active {activate}
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

void Collider::ShowCollider()
{
	std::cout << _active << std::endl;
}
