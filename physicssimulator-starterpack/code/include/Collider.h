#pragma once
#include <iostream>

enum ColliderType { PLANE, SPHERE, CAPSULE };

class Collider
{
protected:
	
	ColliderType _colliderType;
	bool _active;

public:

	Collider();
	Collider(bool activate);

	~Collider();

	void SetActive(bool active);
	bool GetActive();

	ColliderType GetColliderType();

	void ShowCollider();
};