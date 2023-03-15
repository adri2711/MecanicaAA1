#include "Plane.h"

Plane::Plane(glm::vec3 coordinates, glm::vec3 sizes) : _coordinates{ coordinates }, _sizes{ sizes }
{
	CalculateNormalNormalized();
}

void Plane::CalculateNormalNormalized()
{
	glm::vec3 auxVectors[2];

	if (_sizes.x == 0)
	{
		#pragma region XPanels
		if (_coordinates.x == -5) //LeftPanel
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
	else if (_sizes.y == 0)
	{
		#pragma region YPanels
		if (_coordinates.y == 0) //BottomPanel
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
	else if (_sizes.z == 0)
	{
		#pragma region ZPanels
		if (_coordinates.z == -5) //FrontPanel
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
