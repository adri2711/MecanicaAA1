#pragma once
#include <glm/detail/type_vec3.hpp>

enum ColliderType { PLANE, SPHERE, CAPSULE };

class Collider
{
protected:
	
	ColliderType _colliderType;
	bool _active;

public:

	Collider();
	Collider(bool activate, ColliderType colliderType);

	~Collider();

	void SetActive(bool active);
	bool GetActive();

	ColliderType GetColliderType();
};