#pragma once

#include <vector>

#include "ColliderSystem.h"
#include "../MeshNode.h"

#define WIDTH 14
#define HEIGHT 18

#define MIN_DISTANCE_BETWEEN_PARTICLES 0.4f
#define MAX_DISTANCE_BETWEEN_PARTICLES 1.f

#define MIN_STRUCTURAL_RIGIDITY 1.0f
#define MAX_STRUCTURAL_RIGIDITY 500.0f

#define MIN_STRUCTURAL_DAMPING 0.0f
#define MAX_STRUCTURAL_DAMPING 10.0f

#define MIN_SHEAR_RIGIDITY 1.0f
#define MAX_SHEAR_RIGIDITY 350.0f

#define MIN_SHEAR_DAMPING 0.0f
#define MAX_SHEAR_DAMPING 10.0f

#define MIN_BEND_RIGIDITY 1.0f
#define MAX_BEND_RIGIDITY 250.0f

#define MIN_BEND_DAMPING 0.0f
#define MAX_BEND_DAMPING 10.0f

class Mesh
{

private:

	std::vector<MeshNode> _meshNodes;
	std::vector<glm::vec3> _positions;
	glm::vec3 _startPosition;

public:

	float _distanceBetweenParticles;
	float _structuralElasticity;
	float _structuralDamping;
	float _shearElasticity;
	float _shearDamping;
	float _bendElasticity;
	float _bendDamping;

	Mesh(glm::vec3 startPosition, float distanceBetweenParticles, float structuralElasticity, float structuralDamping,
		float shearElasticity, float bendElasticity, float shearDamping, float bendDamping);
	~Mesh();

	void ConnectNodesWithSprings();

	void CreateSprings(int i);
	void CheckStructuralSprings(int i);
	void CheckShearSprings(int i);
	void CheckBendSprings(int i);

	bool CheckNodeMeshConnections(int i, int meshNodeIndexToConnect);

	void CreateStructuralSpring(int i, int meshNodeIndexToConnect);
	void CreateShearSpring(int i, int meshNodeIndexToConnect);
	void CreateBendSpring(int i, int meshNodeIndexToConnect);

	const float* GetFirstPosition();
	void UpdateNodesPositions(std::vector<Collider*> colliders, float dt);

	std::vector<glm::vec3> GetPositions();

	float GetDistanceBetweenParticles();
	float GetStructuralElasticity();
	float GetStructuralDamping();
	float GetShearElasticity();
	float GetShearDamping();
	float GetBendElasticity();
	float GetBendDamping();
};

