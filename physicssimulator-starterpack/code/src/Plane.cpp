#include "Plane.h"

Plane::Plane(glm::vec3 coordinates, glm::vec3 sizes, char heightCoordinate, char widthCoordinate) : _coordinates{ coordinates }, _sizes{ sizes }
{
	CalculateNormal();
}

void Plane::CalculateNormal()
{
	glm::vec3 auxVectors[2];

	auxVectors[0].x = _coordinates.x - _sizes.x * 0;
	auxVectors[0].y = _coordinates.y - _sizes.y * 1;
	auxVectors[0].z = _coordinates.z - _sizes.z * 0;

	auxVectors[1].x = _coordinates.x - _sizes.x * 1;
	auxVectors[1].y = _coordinates.y - _sizes.y * 0;
	auxVectors[1].z = _coordinates.z - _sizes.z * 0;

	_normal.x = auxVectors[0].y * auxVectors[1].z - auxVectors[0].z * auxVectors[1].y;
	_normal.y = auxVectors[0].x * auxVectors[1].z - auxVectors[0].z * auxVectors[1].x;
	_normal.z = auxVectors[0].x * auxVectors[1].y - auxVectors[0].y * auxVectors[1].x;
}

glm::vec3 Plane::GetNormal()
{
	return _normal;
}

glm::vec3 Plane::GetCollisionPoint()
{
	return glm::vec3();
}

glm::vec3 Plane::GetNewPoint()
{
	return glm::vec3();
}
