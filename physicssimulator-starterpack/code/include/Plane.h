#pragma once
#include <RenderPrims.h>

class Plane
{
private:

	glm::vec3 _coordinates;
	glm::vec3 _sizes;
	glm::vec3 _normal;

	void CalculateNormalNormalized();

public:

	Plane(glm::vec3 coordinates, glm::vec3 sizes);

	glm::vec3 GetNormal();
	glm::vec3 GetCollisionPoint();
	glm::vec3 GetNewPoint();

};