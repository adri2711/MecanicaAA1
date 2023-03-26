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
    Sphere* _sphere;
    Capsule* _capsule;
     
    void UpdatePrimitive();    

public:

    ColliderSystem();
    ~ColliderSystem();

    void SetSphere(Sphere* sphere);
    Sphere* GetSphere();
    
    void SetCapsule(Capsule* capsule);
    Capsule* GetCapsule();
    
    virtual void Render();
    
};
