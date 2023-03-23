#pragma once
#include <glm/detail/type_vec3.hpp>

enum ColliderType { PLANE, SPHERE, CAPSULE };

class Collider
{
protected:
	
	ColliderType _colliderType;
	bool _active;
	glm::vec3 _normal;
	float _d;

public:

	Collider();
	Collider(bool activate, ColliderType colliderType);

	~Collider();

	void SetActive(bool active);
	bool GetActive();

	void SetNormal(glm::vec3 normal);
	glm::vec3 GetNormal();

	void SetD(float d);
	float GetD();

	ColliderType GetColliderType();
};