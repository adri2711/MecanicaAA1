#pragma once
#include <RenderPrims.h>
#include "Collider.h"

class Plane : public Collider
{
private:

	glm::vec3 _coordinates;
	glm::vec3 _sizes;
	glm::vec3 _normal;
	float _d;

	glm::vec3 CalculateNormalNormalized();
	float CalculateD();

public:

	Plane(glm::vec3 coordinates, glm::vec3 sizes);
	~Plane();

};