#include "Plane.h"

Plane::Plane(glm::vec3 coordinates, glm::vec3 sizes) : _coordinates{ coordinates }, _sizes{ sizes }
{
	_colliderType = PLANE;
	CalculateNormalNormalized();
}

Plane::~Plane()
{
	delete this;
}

void Plane::CalculateNormalNormalized()
{
	glm::vec3 auxVectors[2];

	if (_sizes.x == 0.f)
	{
		#pragma region XPanels
		if (_coordinates.x == -5.f) //LeftPanel
		{
			auxVectors[0] = _sizes * glm::vec3(0, 1, 0);
			auxVectors[1] = _sizes * glm::vec3(0, 0, 1);
		}
		else //RightPanel
		{
			auxVectors[0] = _sizes * glm::vec3(0, 0, 1);
			auxVectors[1] = _sizes * glm::vec3(0, 1, 0);
		}
		#pragma endregion
	}
	else if (_sizes.y == 0.f)
	{
		#pragma region YPanels
		if (_coordinates.y == 0.f) //BottomPanel
		{
			auxVectors[0] = _sizes * glm::vec3(0, 0, 1);
			auxVectors[1] = _sizes * glm::vec3(1, 0, 0);			
		}
		else //TopPanel
		{
			auxVectors[0] = _sizes * glm::vec3(1, 0, 0);
			auxVectors[1] = _sizes * glm::vec3(0, 0, 1);
		}
		#pragma endregion
	}
	else if (_sizes.z == 0.f)
	{
		#pragma region ZPanels
		if (_coordinates.z == -5.f) //FrontPanel
		{
			auxVectors[0] = _sizes * glm::vec3(1, 0, 0);
			auxVectors[1] = _sizes * glm::vec3(0, 1, 0);
		}
		else //BackPanel
		{			
			auxVectors[0] = _sizes * glm::vec3(0, 1, 0);
			auxVectors[1] = _sizes * glm::vec3(1, 0, 0);
		}
		#pragma endregion
	}

	_normal.x = auxVectors[0].y * auxVectors[1].z - auxVectors[0].z * auxVectors[1].y;
	_normal.y = auxVectors[0].x * auxVectors[1].z - auxVectors[0].z * auxVectors[1].x;
	_normal.z = auxVectors[0].x * auxVectors[1].y - auxVectors[0].y * auxVectors[1].x;

	_normal /= sqrt(pow(_normal.x, 2) + pow(_normal.y, 2) + pow(_normal.z, 2));
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
