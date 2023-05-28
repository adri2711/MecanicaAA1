#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <cstdio>

#include "RigidbodySim.h"
#include "ParticleSim.h"
#include "ClothSim.h"
#include "FluidSim.h"

#pragma region simulationSelection
enum class EnabledSimulation {
	PARABOLA, CLOTH, RIGIDBODY, FLUID
};

Simulator* currentSimulator;
EnabledSimulation currentSimulation;

void setSimulation(EnabledSimulation simulation) {
	if (currentSimulation == simulation) {
		return;
	}

	delete currentSimulator;
	currentSimulation = simulation;
	switch (simulation) {
		case EnabledSimulation::PARABOLA:
			printf("Start the random particles simulation\n");
			currentSimulator = new ParticleSim();
			break;

		case EnabledSimulation::CLOTH:
			printf("Start the clothes simulation\n");
			currentSimulator = new ClothSim();
			break;

		case EnabledSimulation::RIGIDBODY:
			printf("Start the clothes simulation\n");
			currentSimulator = new RigidBodySim();
			break;
		case EnabledSimulation::FLUID:
			printf("Start the fluid simulation\n");
			currentSimulator = new FluidSim();
			break;
	}
}
#pragma endregion

#pragma region GUI
bool show_test_window = false;

void GUI() {
	bool show = true;
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Simulation")) {
			if (ImGui::MenuItem("Parabola")) { setSimulation(EnabledSimulation::PARABOLA); };
			if (ImGui::MenuItem("Cloth")) { setSimulation(EnabledSimulation::CLOTH); };
			if (ImGui::MenuItem("Rigidbody")) { setSimulation(EnabledSimulation::RIGIDBODY); };
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Physics Parameters", &show, 0);
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
		currentSimulator->RenderGui();
	}
	
	ImGui::End();
}

#pragma endregion


void PhysicsInit() {
	// The default simulation
	currentSimulation = EnabledSimulation::FLUID;
	currentSimulator = new FluidSim();
}

void PhysicsUpdate(float dt) {
	currentSimulator->Update(dt);
	currentSimulator->RenderUpdate();
}

void PhysicsCleanup() {
	delete currentSimulator;
}