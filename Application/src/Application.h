#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Player.h"
#include "Ball.h"

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
	void PlayersController();

	bool BallCollision(const std::shared_ptr<Player>& player);
	bool UpperBoundCollision(const std::shared_ptr<Player>& player);
	bool LowerBoundCollision(const std::shared_ptr<Player>& player);

private:
	// window
	Window window;
	TimeStep ts;

	// shader
	std::shared_ptr<Shader> shader;

	// entities
	std::shared_ptr<Player> p1, p2;
	std::shared_ptr<Ball> ball;

	// camera
	OrthoCam camera;
};