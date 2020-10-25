#pragma once

class Renderer
{
public:
	static const char* GetVendor();
	static const char* GetRenderer();
	
	static void BackgroundColor(float red, float green, float blue, float alpha);

private:
	Renderer();
};