#pragma once
#include "ParticleSystem.h"
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>
#include <cassert>

#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>

#include "GL_framework.h"

class FountainParticleSystem : public ParticleSystem
{
protected:
	virtual void ParticleUpdate(int i, float dt) override;
	virtual Particle CreateParticle() override;
	glm::vec3 coneDir = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 dirNorm;
public:
	void SetDirection(glm::vec3 dir);
	float angle = 45.f; 
	float velocityMagnitude = 1.f;
	virtual void Setup() override;
};

