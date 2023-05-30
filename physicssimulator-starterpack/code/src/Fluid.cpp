#include "Fluid.h"

#include <iostream>

Fluid::Fluid(glm::vec3 startPosition, float distanceBetweenParticles, float density)
	: _startPosition(startPosition), distanceBetweenParticles(distanceBetweenParticles), density(density)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		float z = startPosition.z - distanceBetweenParticles * i;
		for (int j = 0; j < WIDTH; j++)
		{
			float x = startPosition.x + distanceBetweenParticles * j;
			glm::vec3 FluidNodePosition = glm::vec3(x, _startPosition.y, z);
			_fluidNodes.push_back(FluidNode(FluidNodePosition));
			_positions.push_back(_fluidNodes[i * WIDTH + j].position);
		}
	}
}

Fluid::~Fluid()
{

}

const float* Fluid::GetFirstPosition() 
{
	return &_positions[0].x;
}

void Fluid::UpdateNodesPositions(std::vector<Collider*> colliders, float dt)
{	
	for (int i = 0; i < _fluidNodes.size(); i++)
	{
		_positions[i] = _fluidNodes[i].UpdatePosition(colliders, _waves, dt);		
	}
}

void Fluid::AddWave(Wave newWave)
{
	_waves.push_back(newWave);
}

float Fluid::FindSubmergedVolume(const BuoyantSphere& sphere)
{
	return 0.0f;
}

std::vector<glm::vec3> Fluid::GetPositions()
{
	return _positions;
}