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
	glm::vec3 acc = glm::vec3();
	if (gravity) acc += glm::vec3(0.f, -.098f, 0.f);
	for (int i = 0; i < _forces.size(); i++) {
		acc += _forces[i] / mass;
	}
	_forces.clear();
	velocity += acc * dt;
	_coordinates += velocity * dt;
}
