#pragma once

#include <memory>

#include "VertexArray.h"

class Render
{
public:
	static const char* GetVendor();
	static const char* GetRenderer();
	
	static void BackgroundColor(float red, float green, float blue, float alpha);
	
	static void BeginScene();
	static void EndScene();
	static void DrawIndexed(const std::shared_ptr<VertexArray>& va);

private:
	Render() = default;
};