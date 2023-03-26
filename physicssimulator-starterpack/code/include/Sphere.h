#pragma once
#include "Collider.h"

class Sphere : public Collider
{

#define MIN_X_POSITION -5
#define MAX_X_POSITION 5

#define MIN_Y_POSITION 0 
#define MAX_Y_POSITION 10

#define MIN_Z_POSITION -5
#define MAX_Z_POSITION 5

#define MIN_RADIUS 0.5f
#define MAX_RADIUS 5
	
private:

public:

	glm::vec3 _coordinates;
	float _radius;
	
	Sphere(glm::vec3 coordinates, float radius);
	~Sphere();
	
	float CalculateA(glm::vec3 currentPosition);
	float CalculateB(glm::vec3 currentPosition, glm::vec3 vectorBetweenPositions);
	float CalculateC(glm::vec3 vectorBetweenCoordinates);

};

