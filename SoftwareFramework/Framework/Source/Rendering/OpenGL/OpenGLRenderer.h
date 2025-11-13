#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "../Renderer2D.h"
#include "Vendor/glm/glm.hpp"

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			class OpenGLRenderer : public Renderer2D
			{
			private:
				GLFWwindow* window;

				int width;
				int height;
				std::string title;

				int x;
				int y;

				glm::mat4 projection;

			public:

				
				OpenGLRenderer();
				~OpenGLRenderer();

				void Init() override;
				void CreateWindow(int height, int width, const char* title, int x = 1, int y = 1) override;

				void SetBackgroundColor(int color) override;
				void DrawTriangle(float ax, float ay, float bx, float by, float cx, float cy, int color) override;
				void DrawSquare(float x, float y, float width, float height, int color) override;
				void DrawImage(float x, float y, float width, float height, int color, std::string imageFilePath) override;

				void Update(float deltaTime) override;

				static OpenGLRenderer& GetInstance();
				
			private:
				static void WindowSizeChangedCallback(GLFWwindow* window, int width, int height);


			};
		}
	}
}