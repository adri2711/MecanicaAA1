#pragma once
#include "glm/glm.hpp"
#include <time.h>

#define MIN_ANGLE 0.0f
#define MAX_ANGLE 360.0f
#define MIN_AMPLITUDE 0.0f
#define MAX_AMPLITUDE 1.0f
#define MIN_WAVELENGTH 0.1f
#define MAX_WAVELENGTH 1.0f
#define MIN_PHASE 0.0f
#define MAX_PHASE 5.0f
#define DEFAULT_WAVE Wave(rand() % 360, .3f, 0.2f, 0.f)

class Wave
{
public:
	glm::vec3 direction;
	float angle;
	float phi;
	float amplitude;
	float wavelength;

	Wave(float angle, float amplitude, float wavelength, float phi);
	glm::vec3 GetPositionAtTime(glm::vec3 initialPos, float t);
};

