#include "Fluid.h"

#include <iostream>

Fluid::Fluid(glm::vec3 startPosition, float distanceBetweenParticles, float density)
	: _startPosition(startPosition), distanceBetweenParticles(distanceBetweenParticles), density(density)
{
	t = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		float z = startPosition.z - distanceBetweenParticles * i;
		for (int j = 0; j < WIDTH; j++)
		{
			float x = startPosition.x + distanceBetweenParticles * j;
			glm::vec3 FluidNodePosition = glm::vec3(x, _startPosition.y, z);
			_fluidNodes.push_back(new FluidNode(FluidNodePosition));
			_positions.push_back(_fluidNodes[i * WIDTH + j]->position);
		}
	}
}

Fluid::~Fluid()
{
	for (int i = 0; i < _fluidNodes.size(); i++) {
		delete _fluidNodes[i];
	}
}

const float* Fluid::GetFirstPosition() 
{
	return &_positions[0].x;
}

void Fluid::UpdateNodesPositions(std::vector<Collider*> colliders, float dt)
{	
	for (int i = 0; i < _fluidNodes.size(); i++)
	{
		_positions[i] = _fluidNodes[i]->UpdatePosition(colliders, _waves, t);		
	}
	t += dt;
}

void Fluid::AddWave(Wave newWave)
{
	_waves.push_back(newWave);
}

float Fluid::FindSubmergedVolume(const BuoyantSphere& sphere)
{
	int submergedPoints = 0;
	for (int i = 0; i < sphere.samplePoints.size(); i++) {
		glm::vec3 wavePos = glm::vec3(0.f, _startPosition.y, 0.f);
		glm::vec3 point = sphere.samplePoints[i] + sphere._coordinates;
		for (int j = 0; j < _waves.size(); j++) {
			wavePos += _waves[j].GetPositionAtTime(point, t);
		}
		//std::cout << wavePos.y << " < " << point.y << std::endl;
		if (wavePos.y >= point.y) {
			submergedPoints++;
		}
	}
	float ratio = submergedPoints / (float)sphere.samplePoints.size();
	float volume = 4.18879 * glm::pow(sphere._radius, 3);
	//if (ratio > 0) std::cout << "Ratio:" << ratio << std::endl;
	return volume * ratio;
}

std::vector<glm::vec3> Fluid::GetPositions()
{
	return _positions;
}