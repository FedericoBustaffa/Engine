#pragma once

#include <vector>
#include <memory>

#include "Window.h"

#include "Render/VertexArray.h"
#include "Render/Buffer.h"
#include "Render/Shader.h"

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

private:
	// window
	Window window;

	// rendering objects
	std::shared_ptr<VertexArray> triangle_va;
	std::shared_ptr<Buffer> triangle_vb;
	std::shared_ptr<IndexBuffer> triangle_ib;

	std::shared_ptr<VertexArray> square_va;
	std::shared_ptr<Buffer> square_vb;
	std::shared_ptr<IndexBuffer> square_ib;
	
	std::shared_ptr<Shader> red_shader;
	std::shared_ptr<Shader> blue_shader;
};