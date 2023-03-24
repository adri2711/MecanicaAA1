#pragma once
#include "Collider.h"

class Sphere : public Collider
{
private:

	glm::vec3 _coordinates;
	float _radius;

public:

	Sphere(glm::vec3 coordinates, float radius);
	~Sphere();

	glm::vec3 GetCoordinates();
	
	float GetRadius();

	float CalculateA(glm::vec3 currentPosition);
	float CalculateB(glm::vec3 currentPosition, glm::vec3 vectorBetweenPositions);
	float CalculateC(glm::vec3 vectorBetweenCoordinates);

};

