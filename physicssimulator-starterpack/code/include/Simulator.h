#pragma once
#include <vector>
#include "Collider.h"

class Simulator {
protected:
	std::vector<Collider*> _colliders;

public:
	virtual void Update(float dt) = 0;
	virtual void RenderUpdate() = 0;
	virtual void RenderGui() = 0;

	void AddCollider(Collider* collider) {
		_colliders.push_back(collider);
	}

	virtual ~Simulator() {};
};