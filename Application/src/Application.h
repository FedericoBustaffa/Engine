#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Core/Window.h"
#include "Core/TimeStep.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"
#include "Graphics/Shader.h"
#include "Graphics/OrthoCam.h"

#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

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
	void SquareTransform();

private:
	// window
	Window window;
	TimeStep ts;

	// rendering objects
	std::shared_ptr<Shader> shader;
	glm::mat4 model;

	// square
	std::shared_ptr<VertexArray> squareVA;
	std::shared_ptr<Buffer> squareVB;
	std::shared_ptr<IndexBuffer> squareIB;
	glm::vec3 square_position = { 0.0, 0.0, 0.0 };
	float square_speed = 1.0f;
	bool right = false, left = false, up = false, down = false;

	// camera
	OrthoCam camera;
	glm::vec3 camera_position = { 0.0, 0.0, 0.0 };
	float camera_rotation = 0.0f;
	float camera_speed = 15.0f, camera_rotation_speed = 180.0f;
};