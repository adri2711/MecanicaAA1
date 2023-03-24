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

	void CalculateNormalNormalized();

public:

	Plane(glm::vec3 coordinates, glm::vec3 sizes);
	Plane(glm::vec3 coordinates);
	~Plane();

	
	void SetNormal(glm::vec3 normal);
	glm::vec3 GetNormal();
	
	void CalculateD();
	float GetD();

};