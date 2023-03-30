#include "Mesh.h"

Mesh::Mesh(glm::vec3 startPosition, float distanceBetweenParticles) : _startPosition(startPosition), _distanceBetweenParticles(distanceBetweenParticles)
{
	for (int i = 0; i < MIN_HEIGHT_LENGTH; i++)
	{
		float z = startPosition.z - _distanceBetweenParticles * i;
		for (int j = 0; j < MIN_WIDTH_LENGTH; j++)
		{
			float x = startPosition.x + _distanceBetweenParticles * j;
			_positions.push_back(glm::vec3(x, _startPosition.y, z));
		}
	}
}

Mesh::~Mesh()
{	
}

const float* Mesh::GetFirstPosition() 
{
	return &_positions[0].x;
}

void Mesh::UpdatePosition(float dt)
{
	for (int i = 0; i < MIN_HEIGHT_LENGTH; i++)
	{
		for (int j = 0; j < MIN_WIDTH_LENGTH; j++)
		{
			
		}
	}
}