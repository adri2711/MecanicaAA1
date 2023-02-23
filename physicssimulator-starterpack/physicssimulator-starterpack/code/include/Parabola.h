#pragma once
#include <Simulator.h>
#include <RenderPrims.h>

class ParabolaSim : public Simulator {
public:
	ParabolaSim();
	~ParabolaSim();

	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;

private:
	graphics::ParticlesPrimitive* particlesPrim;

	glm::vec3 x0[2];
	glm::vec3 x[2];
	glm::vec3 v0[2];
	glm::vec3 a;

	glm::vec3 EulerSolver(float time, int iteration);
};