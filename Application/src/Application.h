#pragma once

#include <vector>
#include <memory>

#include "Core/Window.h"
#include "Core/TimeStep.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"
#include "Graphics/Shader.h"

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
	TimeStep ts;

	// rendering objects
	std::shared_ptr<Shader> shader;

	std::shared_ptr<VertexArray> va;
	std::shared_ptr<Buffer> vb;
	std::shared_ptr<IndexBuffer> ib;
};