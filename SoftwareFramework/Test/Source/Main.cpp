#define GLEW_STATIC

#include <chrono>
#include <iostream>
#include "Manager.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/OpenGL/OpenGLRenderer.h"
#include <thread>

using Framework::Rendering::Renderer2D;

Renderer2D* renderer;

int i = 0;
static void Update(float deltaTime)
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
		Renderer2D::GetInstance().SetBackgroundColor(r % 255 | (g % 256 << 8) | (b % 256 << 16) | (255 % 256 << 24));
		Renderer2D::GetInstance().DrawImage(200, 200, 250, 250, r % 256 | (g % 256 << 8) | (b % 256 << 16) | (255 % 256 << 24), "Resources\\image0.png");
	}
	else
	{
		Renderer2D::GetInstance().SetBackgroundColor(0 % 256 | (0 % 256 << 8) | (0 % 256 << 16) | (255 % 256 << 24));
		Renderer2D::GetInstance().DrawImage(450, 450, 250, 250, 255 % 256 | (255 % 256 << 8) | (255 % 256 << 16) | (255 % 256 << 24), "Resources\\image1.jpg");
	}

	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(1000ms);

}

int main()
{	
	Framework::Manager* manager = new Framework::Manager(Update);

	renderer = new Framework::Rendering::OpenGl::OpenGLRenderer();

	Renderer2D::GetInstance().Init();
	Renderer2D::GetInstance().CreateWindow(900, 900, "Test", 15, 15);

	manager->Init(&Renderer2D::GetInstance());

	Renderer2D::GetInstance().~Renderer2D();
	
}
