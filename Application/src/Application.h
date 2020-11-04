#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Triangle.h"

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

	void CameraController();
	void Movement();

private:
	// window
	Window window;
	TimeStep ts;

	// shader
	std::shared_ptr<Shader> shader;

	
	// triangle
	glm::vec4 vertices[3] = {
		{ -1.0f, -1.0f, 0.0f, 1.0f },
		{  0.0f,  1.0f, 0.0f, 1.0f },
		{  1.0f, -1.0f, 0.0f, 1.0f },
	};

	std::shared_ptr<Triangle> triangle;


	// camera
	OrthoCam camera;
	glm::vec3 camera_position = { 0.0, 0.0, 0.0 };
	float camera_rotation = 0.0f;
	float camera_speed = 15.0f, camera_rotation_speed = 180.0f;
};