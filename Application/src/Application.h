#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Player.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

	// eventi
	void OnEvent(Event& e);
	void OnCloseEvent(CloseEvent& e);
	void OnKeyPressedEvent(KeyPressedEvent& e);

	// movimento
	void CameraController();
	void MoveP1();
	void MoveP2();

	bool Collision();
	bool BoundCollision(const std::shared_ptr<Player>& player);

private:
	// window
	Window window;
	TimeStep ts;

	// shader
	std::shared_ptr<Shader> shader;

	// player
	std::shared_ptr<Player> p1, p2;

	// camera
	OrthoCam camera;
	glm::vec3 camera_position = { 0.0, 0.0, 0.0 };
	float camera_rotation = 0.0f;
	float camera_speed = 15.0f, camera_rotation_speed = 180.0f;
};