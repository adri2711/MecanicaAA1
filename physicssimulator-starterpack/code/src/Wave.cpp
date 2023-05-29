#include "Wave.h"

Wave::Wave(glm::vec3 direction, float amplitude, float wavelength, float phi)
{
	this->direction = direction;
	this->amplitude = amplitude;
	this->wavelength = wavelength;
	this->phi = phi;
}

glm::vec3 Wave::GetPositionAtTime(glm::vec3 initialPos, float t)
{
	glm::vec3 res;
	float k = 6.28318530718 / wavelength;
	float w = 1.f / wavelength;
	float a = glm::dot(direction, initialPos) - w * t + phi;
	res = (direction / k) * amplitude * glm::sin(a);
	res.y = amplitude * glm::cos(a);
	return res;
}
