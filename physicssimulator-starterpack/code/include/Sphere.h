#pragma once
#include "Collider.h"

class Sphere : public Collider
{
private:

	glm::vec3 _coordinates;
	float _radius;
	glm::vec3 _normal;
	float _d;


	glm::vec3 CalculateNormalNormalized() override;
	float CalculateD() override;

public:

	Sphere(glm::vec3 coordinates, float radius);
	~Sphere();

};

