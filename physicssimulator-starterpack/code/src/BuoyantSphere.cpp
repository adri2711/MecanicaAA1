#include "BuoyantSphere.h"
#include <iostream>

BuoyantSphere::BuoyantSphere(glm::vec3 coordinates, float radius, float mass, bool hasGravity) : Sphere(coordinates, radius)
{
	this->mass = mass;
	this->hasGravity = hasGravity;
	gravity = glm::vec3(0.f, mass * -9.8f, 0.f);

	float stride = (radius * 2) / SAMPLE_SEGMENTS;
	glm::vec3 basePos = glm::vec3(-radius, -radius, -radius);
	for (int i = 0; i < SAMPLE_SEGMENTS; i++) {
		for (int j = 0; j < SAMPLE_SEGMENTS; j++) {
			for (int k = 0; k < SAMPLE_SEGMENTS; k++) {
				glm::vec3 pos = basePos + glm::vec3(k * stride, j * stride, i * stride);
				float d = pos.x * pos.x + pos.y * pos.y + pos.z * pos.z;
				if (d <= radius * radius) {
					samplePoints.push_back(pos);
				}
			}
		}
	}
}

void BuoyantSphere::AddForce(glm::vec3 force)
{
	_forces.push_back(force);
}

void BuoyantSphere::ApplyBuoyancyForce(float density, float volume)
{
	//std::cout << "density:" << density << std::endl;
	//std::cout << "gravity:" << -gravity.y << std::endl;
	//std::cout << "volume" << volume << std::endl;
	glm::vec3 force = glm::vec3(0.f, density * -gravity.y * volume, 0.f);
	//std::cout << "force:" << force.y << std::endl;
	AddForce(force);
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
