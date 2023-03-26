#pragma once
#include <glm/detail/type_vec3.hpp>

enum ColliderType { PLANE, SPHERE, CAPSULE };

class Collider
{
protected:
	
	ColliderType _colliderType;

public:

	Collider();
	Collider(bool activate, ColliderType colliderType);

	~Collider();

	ColliderType GetColliderType();
};