#define GLEW_STATIC

#include <chrono>
#include <iostream>
#include "Manager.h"
#include "Rendering/Renderer.h"
#include "Rendering/OpenGL/OpenGLRenderer.h"
#include <thread>


#include "PreFramework.h"

Framework::Rendering::Renderer2D* renderer;

int i = 0;
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
	i++;
	i %= 2;

	if (i == 0)
	{
		renderer->BackgroundColor(0 % 255 | (0 % 255 << 8) | (0 % 255 << 16) | (254 << 24));
		renderer->DrawTriangle(0.0, 0.0, 0.0, -0.5, -0.5, 0.0, r % 255 | (g % 255 << 8) | (b % 255 << 16) | (254 << 24));
		renderer->DrawTriangle(0.0, -0.5, -0.5, -0.5, -0.5, 0.0, r % 255 | (g % 255 << 8) | (b % 255 << 16) | (254 << 24));
	}
	else
	{
		renderer->BackgroundColor(r % 255 | (g % 255 << 8) | (b % 255 << 16) | (254 << 24));
		renderer->DrawTriangle(0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0 % 255 | (0 % 255 << 8) | (0 % 255 << 16) | (254 << 24));
		renderer->DrawTriangle(0.0, 0.5, 0.5, 0.5, 0.5, 0.0, 0 % 255 | (0 % 255 << 8) | (0 % 255 << 16) | (254 << 24));
	}

	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(500ms);
}

void RenderTest()
{
	
}

int main()
{
	Run();
	return 0;

	Framework::Manager* manager = new Framework::Manager(Update);

	renderer = new Framework::Rendering::OpenGl::OpenGLRenderer();

	renderer->Init();
	renderer->CreateWindow(300, 300, "Test", 15, 15);

	manager->Init(renderer);

	renderer->~Renderer2D();
}
