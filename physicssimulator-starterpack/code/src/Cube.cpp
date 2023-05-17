#include "Cube.h"

#include <iostream>

glm::mat3 Cube::CalculateIBody()
{
    glm::mat3 temp= {

        glm::vec3((_mass / 12.f) * (pow(_scale.z, 2.f) + pow(_scale.y, 2.f)), 0.f, 0.f),
        glm::vec3(0.f, (_mass / 12.f) * (pow(_scale.x, 2.f) + pow(_scale.y, 2.f)), 0.f),
        glm::vec3( 0.f, 0.f, (_mass / 12.f) * (pow(_scale.x, 2.f) + pow(_scale.z, 2.f))),
        
    };

    return temp;
}

Cube::Cube(float initialRotation, glm::vec3 initialDirection, glm::vec3 centerOfMass, glm::vec3 scale, float mass,
    glm::vec3 linearVelocity, glm::vec3 angularVelocity, std::vector<glm::vec3> particlesLocalPosition):
    RigidBody(initialRotation, initialDirection, centerOfMass, mass,
        linearVelocity, angularVelocity, scale, glm::mat3(), particlesLocalPosition)
{
    
    srand(time(NULL));

    _scale = scale;
    _iBody = {

        glm::vec3((_mass / 12.f) * (pow(_scale.z, 2.f) + pow(_scale.y, 2.f)), 0.f, 0.f),
        glm::vec3(0.f, (_mass / 12.f) * (pow(_scale.x, 2.f) + pow(_scale.y, 2.f)), 0.f),
        glm::vec3(0.f, 0.f, (_mass / 12.f) * (pow(_scale.x, 2.f) + pow(_scale.z, 2.f))),

    };
    _cube = manager.NewCube(glm::mat4(1.f));

    for (int i = 0; i < _particlesWorldPosition.size(); ++i)
    {
        _spheres.push_back(Sphere(_particlesWorldPosition[i], 0.2f));
        _spheresPrimitive.push_back(manager.NewSphere(_spheres[i]._coordinates, _spheres[i]._radius));
    }

    _cube->Update(_state.positionMatrix * glm::mat4(QuaternionToMatrix(_state.rotationQuaternion)));
}

Cube::~Cube()
{
    manager.DestroyPrimitive(_cube);

    for (int i = 0; i < _spheresPrimitive.size(); ++i)
    {
        manager.DestroyPrimitive(_spheresPrimitive[i]);
    }
}

void Cube::Update(float dt)
{   
    // Abel test movement
    //_state.rotationQuaternion *= CalculateRotationQuaternion(glm::radians(float((int)ImGui::GetTime() % 360)), glm::vec3(5, 2, -3.f));
    //_state.positionMatrix = CalculatePositionMatrix(glm::vec3(sinf(ImGui::GetTime()) * 5.f, 5.f + cosf(ImGui::GetTime()) * 5.f, 0.f));

    RigidBody::Update(dt);

    _cube->Update(_state.positionMatrix * glm::mat4(QuaternionToMatrix(_state.rotationQuaternion)));

    //Abel debug spheres
    for (int i = 0; i < _spheres.size(); ++i)
    {
        _spheres[i]._coordinates = _particlesWorldPosition[i];
        _spheresPrimitive[i]->Update(_spheres[i]._coordinates, _spheres[i]._radius);
    }
}