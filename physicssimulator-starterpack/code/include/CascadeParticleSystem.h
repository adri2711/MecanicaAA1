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

class CascadeParticleSystem : public ParticleSystem
{
protected:
	virtual void ParticleUpdate(int i, float dt) override;
	virtual Particle CreateParticle() override;
	glm::vec3 dirNormalised = glm::vec3(0.f, 0.f, 0.f);
public:
	glm::vec3 startPoint = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 endPoint = glm::vec3(0.f, 0.f, 0.f);
	float rotationAngle = 60.f; 
	float velocityMagnitude = 1.f;
	virtual void Setup() override;
};

