#include "ColliderSystem.h"

extern graphics::PrimitiveManager manager;

ColliderSystem::ColliderSystem()
{ 
}

ColliderSystem::~ColliderSystem()
{
    ResetColliderSystem();
}

void ColliderSystem::ResetColliderSystem()
{
    manager.DestroyPrimitive(_spherePrimitive);
    manager.DestroyPrimitive(_capsulePrimitive);
    delete _sphere;
    delete _capsule;
}

void ColliderSystem::Render() {
    for (int i = 0; i < _colliders.size(); ++i)
    {
        if (_colliders[i]->GetColliderType() == SPHERE)
        {            
            Sphere* sphere = reinterpret_cast<Sphere*>(_colliders[i]);
            _spherePrimitive->Update(sphere->_coordinates, sphere->_radius);
        }
        else if(_colliders[i]->GetColliderType() == CAPSULE)
        {
            Capsule* capsule = reinterpret_cast<Capsule*>(_colliders[i]);
            _capsulePrimitive->Update(capsule->_pointACoordinates, capsule->_pointBCoordinates, capsule->_radius);            
        }
    }
}

void ColliderSystem::SetSphere(Sphere* sphere)
{
    _sphere = sphere;
    _spherePrimitive = manager.NewSphere(sphere->_coordinates, sphere->_radius);
    _colliders.push_back(sphere);
}

Sphere* ColliderSystem::GetSphere()
{
    return _sphere;
}

void ColliderSystem::SetCapsule(Capsule* capsule)
{
    _capsule = capsule;
    _capsulePrimitive = manager.NewCapsule(capsule->_pointACoordinates, capsule->_pointBCoordinates, capsule->_radius);
    _colliders.push_back(capsule);
}

Capsule* ColliderSystem::GetCapsule()
{
    return _capsule;
}