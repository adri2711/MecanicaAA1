#pragma once
#include <vector>

#include "Spring.h"
#include "VerletFrame.h"

class MeshNode
{
private:
    
    glm::vec3 _position;
    VerletFrame _verletFrame;
    std::vector<Spring> _springs;
    
public:

    MeshNode(glm::vec3 position);
    ~MeshNode();

    void AddSpring(SpringType springType, float elasticity, float damping, float springLength, int connectPointIndex);
    
    glm::vec3 GetPosition();

    std::vector<Spring> GetSprings();

    void UpdatePosition(float dt);
    
};
