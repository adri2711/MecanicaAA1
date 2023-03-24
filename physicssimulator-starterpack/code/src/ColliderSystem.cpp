#include "ColliderSystem.h"

extern graphics::PrimitiveManager manager;

ColliderSystem::ColliderSystem()
{ 
}

ColliderSystem::~ColliderSystem()
{
    
}

void ColliderSystem::Update(float dt, std::vector<Collider*> colliders)
{
    
}

void ColliderSystem::Render() {
    for (int i = 0; i < _colliders.size(); ++i)
    {
        if (_colliders[i]->GetColliderType() == SPHERE)
        {            
            Sphere* sphere = reinterpret_cast<Sphere*>(_colliders[i]);
            _spherePrimitive->Update(sphere->GetCoordinates(), sphere->GetRadius());
        }
        else if(_colliders[i]->GetColliderType() == CAPSULE)
        {
            Capsule* capsule = reinterpret_cast<Capsule*>(_colliders[i]);
            _capsulePrimitive->Update(capsule->GetPointACoordinates(), capsule->GetPointBCoordinates(), capsule->GetRadius());            
        }
    }
}

void ColliderSystem::SetSphere(Sphere* sphere)
{
    _spherePrimitive = manager.NewSphere(sphere->GetCoordinates(), sphere->GetRadius());
    _colliders.push_back(sphere);
}

void ColliderSystem::SetCapsule(Capsule* capsule)
{
    _capsulePrimitive = manager.NewCapsule(capsule->GetPointACoordinates(), capsule->GetPointBCoordinates(), capsule->GetRadius());
    _colliders.push_back(capsule);
}