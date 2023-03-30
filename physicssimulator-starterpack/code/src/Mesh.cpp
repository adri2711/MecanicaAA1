#include "Mesh.h"

Mesh::Mesh(glm::vec3 startPosition, float distanceBetweenParticles, float structuralElasticity, float shearElasticity, float bendElasticity, float damping)
	: _startPosition(startPosition), _distanceBetweenParticles(distanceBetweenParticles), _structuralElasticity(structuralElasticity),
	_shearElasticity(shearElasticity), _bendElasticity(bendElasticity), _damping(damping)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		float z = startPosition.z - _distanceBetweenParticles * i;
		for (int j = 0; j < WIDTH; j++)
		{
			float x = startPosition.x + _distanceBetweenParticles * j;
			glm::vec3 auxPosition = glm::vec3(x, _startPosition.y, z);
			_meshNodes.push_back(MeshNode(auxPosition));
			_positions.push_back(auxPosition);
		}
	}
}

Mesh::~Mesh()
{	
}

void Mesh::ConnectNodesWithSprings()
{
	for (int i = 0; i < _meshNodes.size(); ++i)
	{
		
	}	
}

const float* Mesh::GetFirstPosition() 
{
	return &_positions[0].x;
}

void Mesh::UpdateNodesPositions(float dt)
{
	for (int i = 0; i < _meshNodes.size(); i++)
	{
		if (i == 0 || i == WIDTH - 1)
		{
			continue;
		}
		_meshNodes[i].UpdatePosition(dt);
		_positions[i] = _meshNodes[i].GetPosition();
	}
}