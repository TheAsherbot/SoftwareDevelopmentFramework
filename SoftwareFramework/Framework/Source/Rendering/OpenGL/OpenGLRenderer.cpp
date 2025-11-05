#include <iostream>

#include "OpenGLRenderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "OpenGLHelper.h"
#include "Vendor/glm/gtc/matrix_transform.hpp"

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			OpenGLRenderer::OpenGLRenderer()
			{

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
					glfwTerminate();
				}
				glfwMakeContextCurrent(window);


				GLenum err = glewInit();

				if (err != GLEW_OK)
				{
					std::cout << "GLEW FAILT TO INIT" << std::endl << glewGetErrorString(err) << std::endl;
				}
				else
				{
					std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
				}

				glViewport(0, 0, width, height);

				std::cout << glGetString(GL_VERSION) << std::endl;

				projection = glm::ortho(-1.5f, 1.5f, -1.5f, 1.5f, -1.0f, 1.0f);

				GL_CALL(glEnable(GL_BLEND));
				GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			}

			void OpenGLRenderer::SetBackgroundColor(int color)
			{
				glfwGetFramebufferSize(window, &width, &height);

				glClearColor((unsigned char)(color & 0xff) / 255.0f, (unsigned char)((color >> (8)) & 0xff) / (float)255, (unsigned char)((color >> (16)) & 0xff) / 255.0f, (unsigned char)((color >> (24)) & 0xff) / 255.0f);
			}

			void OpenGLRenderer::DrawTriangle(float ax, float ay, float bx, float by, float cx, float cy, int color)
			{
				float vertecis[6] =
				{
					ax, ay,
					bx, by,
					cx, cy
				};

				unsigned char indexBuffer[3]
				{
					0, 1, 2
				};

				VertexArray vertexArray;
				VertexBuffer vertexBuffer(vertecis, 3 * 2 * sizeof(float));
				VertexBufferLayout vertexBufferLayout;
				vertexBufferLayout.Push<float>(2);

				vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
	
				IndexBuffer indexBufferObject(indexBuffer, 3);

				GL_CALL(glDrawElements(GL_TRIANGLES, indexBufferObject.GetCount(), GL_UNSIGNED_BYTE, nullptr));

			}

			void OpenGLRenderer::DrawSquare(float x, float y, float width, float height, int color)
			{
				float vertecis[8] =
				{
					x, y,
					x, y + height,
					x + width, y + height,
					x + width, y
				};

				unsigned char indexBuffer[6]
				{
					0, 1, 2,
					0, 2, 3
				};

				VertexArray vertexArray;
				VertexBuffer vertexBuffer(vertecis, 4 * 2 * sizeof(float));
				VertexBufferLayout vertexBufferLayout;
				vertexBufferLayout.Push<float>(2);

				vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

				IndexBuffer indexBufferObject(indexBuffer, 6);


				Shader shader("Resources\\Shaders\\BasicVertexShader.shader", "Resources\\Shaders\\ColorFragmentShader.shader");
				shader.Bind();
				shader.SetUniform4Float("u_Color", (unsigned char)(color & 0xff) / 255.0f, (unsigned char)((color >> (8)) & 0xff) / (float)255, (unsigned char)((color >> (16)) & 0xff) / 255.0f, (unsigned char)((color >> (24)) & 0xff) / 255.0f);
				shader.SetUniformMatrix4Float("u_ModelViewProjection", projection);

				GL_CALL(glDrawElements(GL_TRIANGLES, indexBufferObject.GetCount(), GL_UNSIGNED_BYTE, nullptr));
			}

			void OpenGLRenderer::DrawImage(float x, float y, float width, float height, int color, std::string imageFilePath)
			{
				float vertecis[16] =
				{
					x, y, 0, 0,
					x, y + height, 0, 1,
					x + width, y + height, 1, 1,
					x + width, y, 1, 0 
				};

				unsigned char indexBuffer[6]
				{
					0, 1, 2,
					0, 2, 3
				};

				VertexArray vertexArray;
				VertexBuffer vertexBuffer(vertecis, 4 * 4 * sizeof(float));
				VertexBufferLayout vertexBufferLayout;
				vertexBufferLayout.Push<float>(2);
				vertexBufferLayout.Push<float>(2);

				vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

				IndexBuffer indexBufferObject(indexBuffer, 6);
				
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
				glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0));

				glm::mat4 modelViewProjection = projection * view * model;

				Shader shader("Resources\\Shaders\\TextureVertexShader.shader", "Resources\\Shaders\\TextureFragmentShader.shader");
				shader.Bind();
				shader.SetUniform4Float("u_Color", (unsigned char)(color & 0xff) / 255.0f, (unsigned char)((color >> (8)) & 0xff) / (float)255, (unsigned char)((color >> (16)) & 0xff) / 255.0f, (unsigned char)((color >> (24)) & 0xff) / 255.0f);
				shader.SetUniformMatrix4Float("u_ModelViewProjection", modelViewProjection);

				Texture texture(imageFilePath);
				texture.Bind(0);
				shader.SetUniform1Int("u_Texture", 0);

				GL_CALL(glDrawElements(GL_TRIANGLES, indexBufferObject.GetCount(), GL_UNSIGNED_BYTE, nullptr));
			}

			void OpenGLRenderer::Update(float deltaTime)
			{

				// glClear(GL_COLOR_BUFFER_BIT);

				// glDrawArrays(GL_TRIANGLES, 0, 6);

				glfwSwapBuffers(window);

				glClear(GL_COLOR_BUFFER_BIT);

				glfwPollEvents();
			}
		}
	}
}