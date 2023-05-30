#pragma once
#include "Collider.h"
#include <vector>
#include "Sphere.h"
#include <glm/glm.hpp>

#define SAMPLE_SEGMENTS 5

class BuoyantSphere : public Sphere
{
protected:
    std::vector<glm::vec3> _forces;
    
public:
    glm::vec3 velocity;
    float mass;
    glm::vec3 gravity;
    bool hasGravity;
    std::vector<glm::vec3> samplePoints;
    BuoyantSphere(glm::vec3 coordinates, float radius, float mass, bool gravity = true);
    void AddForce(glm::vec3 force);
    void ApplyBuoyancyForce(float density, float volume);
    void Update(float dt);
};

