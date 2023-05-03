#include "AA4.h"

AA4::AA4()
{
	_cube = manager.NewCube(glm::mat4(1.f));
}

AA4::~AA4()
{
	manager.DestroyPrimitive(_cube);
}

void AA4::Update(float dt)
{
}

void AA4::RenderUpdate()
{
	_cube->Update();
}

void AA4::RenderGui()
{
}