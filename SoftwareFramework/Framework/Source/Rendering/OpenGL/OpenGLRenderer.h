#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "../Renderer.h"

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			class OpenGLRenderer : public Renderer2D
			{
			public:

				
				OpenGLRenderer();
				~OpenGLRenderer();

				void Init() override;
				void CreateWindow(int height, int width, const char* title, int x = 1, int y = 1) override;

				void BackgroundColor(int color) override;
				void DrawTriangle(float ax, float ay, float bx, float by, float cx, float cy, int color) override;
				// virtual void DrawTriangle(Vector2 a, Vector2 b, Vector2 c, int color) override;

				void Update(float deltaTime) override;
			
			private:
				GLFWwindow* window;

				int width;
				int height;
				std::string title;

				int x;
				int y;

			};
		}
	}
}