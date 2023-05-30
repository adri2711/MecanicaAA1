#include "Wave.h"

Wave::Wave(float angle, float amplitude, float wavelength, float phi)
{
	this->angle = angle;
	direction = glm::vec3(glm::cos(glm::radians(angle)), 0.f, glm::sin(glm::radians(angle)));
	this->amplitude = amplitude;
	this->wavelength = wavelength;
	this->phi = phi;
}

glm::vec3 Wave::GetPositionAtTime(glm::vec3 initialPos, float t)
{
	direction = glm::vec3(glm::cos(glm::radians(angle)), 0.f, glm::sin(glm::radians(angle)));
	glm::vec3 res;
	float k = 6.28318530718 / wavelength;
	float w = 1.f / wavelength;
	float a = glm::dot(direction, initialPos) - w * t + phi;
	res = (direction / k) * amplitude * glm::sin(a);
	res.y = amplitude * glm::cos(a);
	return res;
}
