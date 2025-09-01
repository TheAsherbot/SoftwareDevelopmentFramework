#pragma once
#include <GLFW/glfw3.h>
#include "../Renderer.h"

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			class OpenGLRenderer : public Renderer
			{
			public:
				OpenGLRenderer();
				~OpenGLRenderer();

				void Init() override;
				void CreateWindow(int height, int width, const char* title, int x = 1, int y = 1) override;

				void Render(int x, int y, int color) override;

				GLFWwindow* window;
			private:
				
				int width;
				int height;
				std::string title;

				int x;
				int y;

			};
		}
	}
}