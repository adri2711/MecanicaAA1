#pragma once
#include "Collider.h"
#include "RenderPrims.h"
#include "PrimitiveManager.h"
#include <vector>

#include "Capsule.h"
#include "Sphere.h"

class ColliderSystem
{

protected:    
    graphics::SpherePrimitive* _spherePrimitive; 
    graphics::CapsulePrimitive* _capsulePrimitive;
    std::vector<Collider*> _colliders;
     
    void UpdatePrimitive();    

public:

    ColliderSystem();
    ~ColliderSystem();

    void SetSphere(Sphere* sphere);
    void SetCapsule(Capsule* capsule);
    
    virtual void Update(float dt, std::vector<Collider*> colliders);
    virtual void Render();
    
};
