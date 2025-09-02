#include <iostream>
#include "Manager.h"
#include "Rendering/Renderer.h"
#include "Rendering/OpenGL/OpenGLRenderer.h"
#include <chrono>

Framework::Rendering::Renderer* renderer;

void Update(float deltaTime)
{
	srand((unsigned int)time(NULL));
	int r, g, b;
	r = (rand());
	g = (rand());
	b = (rand());

	std::cout << "R: " << r % 255 << std::endl;
	std::cout << "G: " << g % 255 << std::endl;
	std::cout << "B: " << b % 255 << std::endl;

	renderer->Render(5, 5, r % 255 | (g % 255 << 8) | (b % 255 << 16) | (254 << 24));
	// std::cin.get();
}

int main()
{
	Framework::Manager* manager = new Framework::Manager(Update);

	renderer = new Framework::Rendering::OpenGl::OpenGLRenderer();

	renderer->Init();
	renderer->CreateWindow(300, 300, "Test", 0, 0);



	manager->Init(renderer);
	
	renderer->~Renderer();
	return 0;
}