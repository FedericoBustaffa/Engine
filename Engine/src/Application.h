#pragma once

#include <vector>

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
	VertexArray* va;
	Buffer* vb;
	IndexBuffer* ib;
	Shader* shader;
};