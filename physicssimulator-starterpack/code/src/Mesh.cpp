#include "Mesh.h"

#include <iostream>

Mesh::Mesh(glm::vec3 startPosition, float distanceBetweenParticles, float structuralRigidity, float structuralDamping,float shearRigidity,
	float shearDamping, float bendRigidity, float bendDamping)
	: _startPosition(startPosition), _distanceBetweenParticles(distanceBetweenParticles), _structuralRigidity(structuralRigidity),
	_structuralDamping(structuralDamping), _shearRigidity(shearRigidity), _shearDamping(shearDamping),
	_bendRigidity(bendRigidity), _bendDamping(bendDamping)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		float z = startPosition.z - _distanceBetweenParticles * i;
		for (int j = 0; j < WIDTH; j++)
		{
			float x = startPosition.x + _distanceBetweenParticles * j;
			glm::vec3 meshNodePosition = glm::vec3(x, _startPosition.y, z);
			_meshNodes.push_back(MeshNode(meshNodePosition));
			_positions.push_back(*_meshNodes[i * WIDTH + j].GetPosition());
		}
	}
	
	ConnectNodesWithSprings();
}

Mesh::~Mesh()
{
	/*for (int i = _meshNodes.size() - 1; i >= 0; i--)
	{	
		delete[] _meshNodes[i].GetPosition();		
	}*/
}

void Mesh::ConnectNodesWithSprings()
{
	for (int i = 0; i < _meshNodes.size(); ++i)
	{
		CreateSprings(i);
	}
}

void Mesh::CreateSprings(int i)
{
	CheckStructuralSprings(i);
	CheckShearSprings(i);
	CheckBendSprings(i);
}

void Mesh::CheckStructuralSprings(int i)
{
	//Top
	if (i - WIDTH >= 0)
	{
		if (CheckNodeMeshConnections(i, i - WIDTH))
		{
			CreateStructuralSpring(i, i - WIDTH);	
		}		
	}

	//Left
	if ((i - 1 + WIDTH) % WIDTH != WIDTH - 1)
	{
		if (CheckNodeMeshConnections(i, i - 1))
		{
			CreateStructuralSpring(i, i - 1);	
		}		
	}

	//Right
	if ((i + 1) % WIDTH != 0)
	{
		if (CheckNodeMeshConnections(i, i + 1))
		{
			CreateStructuralSpring(i, i + 1);	
		}		
	}

	//Bottom
	if (i + WIDTH < _meshNodes.size())
	{
		if (CheckNodeMeshConnections(i, i + WIDTH))
		{
			CreateStructuralSpring(i, i + WIDTH);	
		}		
	}
}

void Mesh::CheckShearSprings(int i)
{
	//Top Left
	if ((i - (WIDTH + 1)) % WIDTH != WIDTH - 1 && i - (WIDTH + 1) >= 0)
	{
		if (CheckNodeMeshConnections(i, i - (WIDTH + 1)))
		{
			CreateShearSpring(i, i - (WIDTH + 1));	
		}		
	}

	//Top Right
	if ((i - (WIDTH - 1)) % WIDTH != 0 && i - (WIDTH - 1) > 0)
	{
		if (CheckNodeMeshConnections(i, i - (WIDTH - 1)))
		{
			CreateShearSpring(i, i - (WIDTH - 1));	
		}		
	}

	//Bottom Left
	if ((i + (WIDTH - 1)) % WIDTH != WIDTH - 1 && i + WIDTH + 1 < _meshNodes.size())
	{
		if (CheckNodeMeshConnections(i, i + (WIDTH - 1)))
		{
			CreateShearSpring(i, i + (WIDTH - 1));	
		}		
	}

	//Bottom Right
	if ((i + (WIDTH + 1)) % WIDTH != 0 && i + WIDTH + 1 < _meshNodes.size())
	{
		if (CheckNodeMeshConnections(i, i + (WIDTH + 1)))
		{
			CreateShearSpring(i, i + (WIDTH + 1));			
		}
	}
}

void Mesh::CheckBendSprings(int i)
{
	//Top
	if (i - WIDTH * 2 >= 0)
	{
		if (CheckNodeMeshConnections(i, i - WIDTH * 2))
		{
			CreateBendSpring(i, i - WIDTH * 2);			
		}
	}

	//Left
	if ((i - 2 + WIDTH) % WIDTH < WIDTH - 2)
	{
		if (CheckNodeMeshConnections(i, i - 2))
		{
			CreateBendSpring(i, i - 2);			
		}		
	}

	//Right
	if ((i + 2) % WIDTH >= 2)
	{
		if (CheckNodeMeshConnections(i, i + 2))
		{
			CreateBendSpring(i, i + 2);			
		}
	}

	//Bottom
	if (i + WIDTH * 2 < _meshNodes.size())
	{
		if (CheckNodeMeshConnections(i, i + WIDTH * 2))
		{
			CreateBendSpring(i, i + WIDTH * 2);	
		}		
	}
}

bool Mesh::CheckNodeMeshConnections(int i, int meshNodeIndexToConnect)
{
	std::vector<Spring> springs = _meshNodes[meshNodeIndexToConnect].GetSprings();

	for (int j = 0; j < springs.size(); ++j)
	{
		if (springs[j].GetConnectionPointIndex() == i)
		{
			return false;
		}
	}
	return true;
}

void Mesh::CreateStructuralSpring(int i, int meshNodeIndexToConnect)
{
	_meshNodes[i].AddSpring(SpringType::STRUCTURAL, _structuralRigidity, _structuralDamping,
		glm::length(*_meshNodes[i].GetPosition() - *_meshNodes[meshNodeIndexToConnect].GetPosition()),
		meshNodeIndexToConnect, _meshNodes[meshNodeIndexToConnect].GetPosition(), _meshNodes[meshNodeIndexToConnect].GetVelocity(),
		_meshNodes[meshNodeIndexToConnect].GetForce());
}

void Mesh::CreateShearSpring(int i, int meshNodeIndexToConnect)
{
	_meshNodes[i].AddSpring(SpringType::SHEAR, _shearRigidity, _shearDamping,
		glm::length(*_meshNodes[i].GetPosition() - *_meshNodes[meshNodeIndexToConnect].GetPosition()),
		meshNodeIndexToConnect, _meshNodes[meshNodeIndexToConnect].GetPosition(), _meshNodes[meshNodeIndexToConnect].GetVelocity(),
		_meshNodes[meshNodeIndexToConnect].GetForce());
}

void Mesh::CreateBendSpring(int i, int meshNodeIndexToConnect)
{
	_meshNodes[i].AddSpring(SpringType::BEND, _bendRigidity, _bendDamping,
		glm::length(*_meshNodes[i].GetPosition() - *_meshNodes[meshNodeIndexToConnect].GetPosition()),
		meshNodeIndexToConnect, _meshNodes[meshNodeIndexToConnect].GetPosition(), _meshNodes[meshNodeIndexToConnect].GetVelocity(),
		_meshNodes[meshNodeIndexToConnect].GetForce());
}

const float* Mesh::GetFirstPosition() 
{
	return &_positions[0].x;
}

void Mesh::UpdateNodesPositions(std::vector<Collider*> colliders, float dt)
{	
	for (int i = 0; i < _meshNodes.size(); i++)
	{
		if (i == 0 || i == WIDTH - 1)
		{
			_meshNodes[i].CalculateTotalForce();
			continue;
		}
		_positions[i] = *_meshNodes[i].UpdatePosition(colliders, dt);		
	}

	for (int i = 0; i < _meshNodes.size(); i++)
	{
		_meshNodes[i].ResetForce();
	}
}

std::vector<glm::vec3> Mesh::GetPositions()
{
	return _positions;
}

float Mesh::GetDistanceBetweenParticles()
{
	return _distanceBetweenParticles;
}

float Mesh::GetStructuralRigidity()
{
	return _structuralRigidity;
}

float Mesh::GetStructuralDamping()
{
	return _structuralDamping;
}

float Mesh::GetShearRigidity()
{
	return _shearRigidity;
}

float Mesh::GetShearDamping()
{
	return _shearDamping;
}

float Mesh::GetBendRigidity()
{
	return _bendRigidity;
}

float Mesh::GetBendDamping()
{
	return _bendDamping;
}