#include "ParticleSystem.h"

extern graphics::PrimitiveManager manager;

void ParticleSystem::Update(float dt)
{
	float emission = 1.f / emissionRate;
	emitTime += dt;
	if (emitTime >= emission) {
		int amount = dt / emission;
		EmitParticles(amount);
		emitTime -= amount * emission;
	}

	positions = new glm::vec3[particles.size()];
	for (int i = 0; i < particles.size(); i++) {
		ParticleUpdate(i, dt);
	}
}

void ParticleSystem::Render() {
	if (particles.empty()) return;
	particlePrimitives->firstParticle = 0;
	particlePrimitives->numParticles = particles.size();
	particlePrimitives->Update(0, particles.size(), &(positions[0].x));
	delete[] positions;
}

glm::vec3 ParticleSystem::EulerSolver(glm::vec3 x0, glm::vec3 v0, float dt)
{
	return x0 + v0 * dt;
}

void ParticleSystem::ParticleUpdate(int i, float dt)
{
	particles[i].velocity = EulerSolver(particles[i].velocity, particles[i].acceleration, dt);
	glm::vec3 auxPosition = EulerSolver(particles[i].position, particles[i].velocity, dt);

	if (auxPosition.y <= 0 || auxPosition.y >= 10 || auxPosition.x <= -5 || auxPosition.x >= 5 || auxPosition.z <= -5 || auxPosition.z >= 5)
	{
		PositionAfterCollision(particles[i].position, auxPosition);
		VelocityAfterCollision(particles[i].velocity);
	}

	particles[i].position = auxPosition;
	positions[i] = particles[i].position;

	particles[i].time += dt;
	if (particles[i].time >= particles[i].lifeTime) {
		DeleteParticle(i);
	}
}

Particle ParticleSystem::CreateParticle()
{
	return Particle(position, startVelocity, gravity, particleLifeTime, particleMass);
}

void ParticleSystem::DeleteParticle(int i)
{
	particles.erase(particles.begin() + i);
	UpdatePrimitive();
}

void ParticleSystem::EmitParticles(int emissionCount)
{
	for (int i = 0; i < emissionCount; i++) {
		particles.push_back(CreateParticle());
	}
	UpdatePrimitive();
}

void ParticleSystem::UpdatePrimitive()
{
	manager.DestroyPrimitive(particlePrimitives);
	particlePrimitives = manager.NewParticles(particles.size());
}

void ParticleSystem::Setup()
{
	emitTime = emissionRate;
}

ParticleSystem::~ParticleSystem()
{
	manager.DestroyPrimitive(particlePrimitives);
}

void PositionAfterCollision(glm::vec3 currentPosition, glm::vec3 newPosition, std::string axis, float point) {

	glm::vec3 normal;
	glm::vec3 pointOnPlane;
	glm::vec3 vectorBetwenPoints;
	float d;
	glm::vec3 collisionPoint;

	if (axis == "x")
	{
		if (point == -5)
		{
			normal = glm::vec3(1.f,0.f,0.f);

			pointOnPlane = glm::vec3(-5.f, 5.f, .0f);

			vectorBetwenPoints = newPosition - currentPosition;

			d = -(normal.x * pointOnPlane.x + normal.y * pointOnPlane.y + normal.z * pointOnPlane.z);

			float alpha = (-d - (normal.x * currentPosition.x + normal.y * currentPosition.y + normal.z * currentPosition.z))
				/ (normal.x * vectorBetwenPoints.x + normal.y * vectorBetwenPoints.y + normal.z * vectorBetwenPoints.z);

			collisionPoint = alpha * vectorBetwenPoints;
		}
		else
		{

		}
	}
	else if (axis == "y") {

		if (point == 0)
		{

		}
		else 
		{

		}		
	}
	else if (axis == "z") {
		
		if (point == -5) {
			
		}
		else 
		{
			
		}
	}
}

void VelocityAfterCollision(glm::vec3 currentVelocity) {
	
}