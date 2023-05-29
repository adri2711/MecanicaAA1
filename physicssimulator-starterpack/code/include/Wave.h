#pragma once
#include "glm/glm.hpp"

class Wave
{
public:
	glm::vec3 direction;
	float phi;
	float amplitude;
	float wavelength;

	Wave(glm::vec3 direction, float amplitude, float wavelength, float phi);
	glm::vec3 GetPositionAtTime(glm::vec3 initialPos, float t);
};

