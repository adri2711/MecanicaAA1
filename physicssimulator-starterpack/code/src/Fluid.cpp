#include "Fluid.h"

#include <iostream>

Fluid::Fluid(glm::vec3 startPosition, float distanceBetweenParticles)
	: _startPosition(startPosition), distanceBetweenParticles(distanceBetweenParticles)
{
	//for (int i = 0; i < HEIGHT; i++)
	//{
	//	float z = startPosition.z - _distanceBetweenParticles * i;
	//	for (int j = 0; j < WIDTH; j++)
	//	{
	//		float x = startPosition.x + _distanceBetweenParticles * j;
	//		glm::vec3 FluidNodePosition = glm::vec3(x, _startPosition.y, z);
	//		_FluidNodes.push_back(FluidNode(FluidNodePosition));
	//		_positions.push_back(_FluidNodes[i * WIDTH + j].position);
	//	}
	//}
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
	//for (int i = 0; i < _FluidNodes.size(); i++)
	//{
	//	if (i == 0 || i == WIDTH - 1)
	//	{
	//		_FluidNodes[i].CalculateTotalForce();
	//		continue;
	//	}
	//	_positions[i] = *_FluidNodes[i].UpdatePosition(colliders, dt);		
	//}

	//for (int i = 0; i < _FluidNodes.size(); i++)
	//{
	//	_FluidNodes[i].ResetForce();
	//}
}

std::vector<glm::vec3> Fluid::GetPositions()
{
	return _positions;
}