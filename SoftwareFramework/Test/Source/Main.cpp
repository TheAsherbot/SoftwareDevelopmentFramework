#define GLEW_STATIC

#include <chrono>
#include <iostream>
#include "Manager.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/OpenGL/OpenGLRenderer.h"
#include <thread>


// #include "PreFramework.h"

Framework::Rendering::Renderer2D* renderer;

int i = 0;
void Update(float deltaTime)
{
	srand((unsigned int)time(NULL));
	int r, g, b;
	r = (rand());
	g = (rand());
	b = (rand());

	i++;
	i %= 2;

	if (i == 0)
	{
		renderer->SetBackgroundColor(r % 255 | (g % 256 << 8) | (b % 256 << 16) | (255 % 256 << 24));
		renderer->DrawImage(-0.5, -0.5, 0.5, 0.5, r % 256 | (g % 256 << 8) | (b % 256 << 16) | (255 % 256 << 24), "Resources\\image0.png");
	}
	else
	{
		renderer->SetBackgroundColor(0 % 256 | (0 % 256 << 8) | (0 % 256 << 16) | (255 % 256 << 24));
		renderer->DrawImage(0, 0, 0.5, 0.5, 255 % 256 | (255 % 256 << 8) | (255 % 256 << 16) | (255 % 256 << 24), "Resources\\image1.jpg");
	}

	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(500ms);
}

void RenderTest()
{
	
}

int main()
{
// 	Run();
// 	return 0;
	
	Framework::Manager* manager = new Framework::Manager(Update);

	renderer = new Framework::Rendering::OpenGl::OpenGLRenderer();

	renderer->Init();
	renderer->CreateWindow(300, 300, "Test", 15, 15);

	manager->Init(renderer);

	renderer->~Renderer2D();
	
}
