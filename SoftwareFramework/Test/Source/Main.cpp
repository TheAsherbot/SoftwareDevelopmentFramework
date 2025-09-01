#include <iostream>
#include "Rendering/Renderer.h"
#include "Rendering/OpenGL/OpenGLRenderer.h"

int main()
{
	Framework::Rendering::Renderer* renderer = new Framework::Rendering::OpenGl::OpenGLRenderer();

	renderer->Init();
	renderer->CreateWindow(300, 300, "Test", 0, 0);
	
	renderer->Render(5, 5, 34 | (105 << 8) | (158 << 16) | (254 << 24));

	std::cin.get();
	renderer->~Renderer();
	return 0;
}