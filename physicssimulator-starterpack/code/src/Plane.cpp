#include "Plane.h"

Plane::Plane(glm::vec3 coordinates, glm::vec3 sizes) : _coordinates{ coordinates }, _sizes{ sizes }, Collider(true, PLANE)
{
	CalculateNormalNormalized();
	CalculateD();
}

Plane::Plane(glm::vec3 coordinates) : _coordinates(coordinates), Collider(true, PLANE)
{
	
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

	_normal = glm::cross(auxVectors[0], auxVectors[1]);

	_normal /= sqrt(pow(_normal.x, 2) + pow(_normal.y, 2) + pow(_normal.z, 2));
}

void Plane::CalculateD()
{
	_d = -(glm::dot(_normal, _coordinates));
}

void Plane::SetNormal(glm::vec3 normal)
{	
	normal /= sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2));
	_normal = normal;
}

glm::vec3 Plane::GetNormal()
{
	return _normal;
}

float Plane::GetD()
{
	return _d;
}