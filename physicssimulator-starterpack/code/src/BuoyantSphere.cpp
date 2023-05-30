#include "BuoyantSphere.h"

BuoyantSphere::BuoyantSphere(glm::vec3 coordinates, float radius, float mass, bool gravity) : Sphere(coordinates, radius)
{
	this->mass = mass;
	this->gravity = gravity;
}

void BuoyantSphere::AddForce(glm::vec3 force)
{
	_forces.push_back(force);
}

void BuoyantSphere::Update(float dt)
{
	if (gravity) _forces.push_back(glm::vec3(0.f, -9.8f, 0.f));
	glm::vec3 acc = glm::vec3();
	for (int i = 0; i < _forces.size(); i++) {
		acc += _forces[i] / mass;
	}
	_forces.clear();
	velocity += acc * dt;
	_coordinates += velocity * dt;
}
