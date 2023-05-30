#pragma once
#include "Collider.h"
#include <vector>
#include "Sphere.h"
class BuoyantSphere : public Sphere
{
protected:
    std::vector<glm::vec3> _forces;
    
public:
    glm::vec3 velocity;
    float mass;
    glm::vec3 gravity;
    bool hasGravity;
    BuoyantSphere(glm::vec3 coordinates, float radius, float mass, bool gravity = true);
    void AddForce(glm::vec3 force);
    void ApplyBuoyancyForce(float density, float volume);
    void Update(float dt);
};

