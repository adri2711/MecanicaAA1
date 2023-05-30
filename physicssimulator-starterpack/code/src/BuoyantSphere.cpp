#include "BuoyantSphere.h"

BuoyantSphere::BuoyantSphere(glm::vec3 coordinates, float radius, float mass, bool hasGravity) : Sphere(coordinates, radius)
{
	this->mass = mass;
	this->hasGravity = hasGravity;
	gravity = glm::vec3(0.f, mass * -9.8f, 0.f);
}

void BuoyantSphere::AddForce(glm::vec3 force)
{
	_forces.push_back(force);
}

void BuoyantSphere::ApplyBuoyancyForce(float density, float volume)
{
	AddForce(glm::vec3(0.f, density * gravity.y * volume, 0.f));
}

void BuoyantSphere::Update(float dt)
{
	glm::vec3 acc = glm::vec3();
	if (hasGravity) AddForce(gravity);
	for (int i = 0; i < _forces.size(); i++) {
		acc += _forces[i] / mass;
	}
	_forces.clear();
	velocity += acc * dt;
	_coordinates += velocity * dt;
}
