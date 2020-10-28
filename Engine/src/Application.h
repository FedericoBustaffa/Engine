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
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
	std::shared_ptr<Shader> shader;
};