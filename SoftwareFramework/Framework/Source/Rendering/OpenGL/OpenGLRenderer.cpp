#include <iostream>

#include "OpenGLRenderer.h"

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			OpenGLRenderer::OpenGLRenderer()
			{
				int x = 0;
			}

			OpenGLRenderer::~OpenGLRenderer()
			{
				glfwDestroyWindow(window);
				glfwTerminate();
			}


			void OpenGLRenderer::Init()
			{
				if (!glfwInit())
				{
					std::cout << "ERROR!" << std::endl;
					return;
				}
				else
				{
					std::cout << "No Error!" << std::endl;
				}
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


			}
			void OpenGLRenderer::CreateWindow(int height, int width, const char* title, int x, int y)
			{
				this->height = height;
				this->width = width;
				this->title = *title;
				this->x = x;
				this->y = y;

				window = glfwCreateWindow(height, width, title, NULL, NULL);
				if (!window)
				{
					std::cout << "Window or OpenGL context creation failed!" << std::endl;
					// Window or OpenGL context creation failed
				}
				glfwMakeContextCurrent(window);
			}

			void makePixel(int x, int y, int r, int g, int b, GLubyte* pixels, int width, int height)
			{
				if (0 <= x && x < width && 0 <= y && y < height) {
					int position = (x + y * width) * 3;
					pixels[position] = r;
					pixels[position + 1] = g;
					pixels[position + 2] = b;
				}
			}

			void OpenGLRenderer::Render(int x, int y, int color)
			{
				glfwGetFramebufferSize(window, &width, &height);
				glViewport(0, 0, width, height);


				glClearColor((unsigned char)(color & 0xff) / 255.0f, (unsigned char)((color >> (8)) & 0xff) / (float)255, (unsigned char)((color >> (16)) & 0xff) / 255.0f, (unsigned char)((color >> (24)) & 0xff) / 255.0f);
				


			}

			void OpenGLRenderer::Update(float deltaTime)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(window);
			}
		}
	}
}