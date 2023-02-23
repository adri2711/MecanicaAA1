#include <Parabola.h>
#include <PrimitiveManager.h>

extern graphics::PrimitiveManager manager;

ParabolaSim::ParabolaSim() {

	x0[0] = glm::vec3(0.0f, 10.0f, 0.0f);

	x0[1] = glm::vec3(10.0f, 5.0f, 0.0f);

	v0[0] = glm::vec3(3.0f, 0.0f, 0.0f);
	v0[1] = glm::vec3(3.0f, 7.0f, 0.0f);

	a = glm::vec3(0.0f, -9.81f, 0.0f);

	particlesPrim = manager.NewParticles(2);
}

ParabolaSim::~ParabolaSim() {
	manager.DestroyPrimitive(particlesPrim);
}

void ParabolaSim::Update(float dt) {
	for (int i = 0; i < 2; i++)
	{
		glm::vec3 particle = EulerSolver(dt, i);
	}
}

void ParabolaSim::RenderUpdate() {
	particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = 2;
	particlesPrim->Update(0, 2, &(x0[0].x));
}

void ParabolaSim::RenderGui() {

}

glm::vec3 ParabolaSim::EulerSolver(float time, int iteration) {
	glm::vec3 auxPosition = x0[iteration] + time * v0[iteration];
	v0[iteration] += time * a;
	/*if (x0.y < 0)
	{
		auxPosition = pos
	}*/
	x0[iteration] = auxPosition;
	return x0[iteration];
}