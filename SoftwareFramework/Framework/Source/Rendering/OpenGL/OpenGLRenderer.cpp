#include <iostream>

#include "OpenGLRenderer.h"

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			

			static unsigned int CompileShader(unsigned int type, const std::string& source)
			{
				unsigned int id = glCreateShader(type);
				const char* src = source.c_str();
				glShaderSource(id, 1, &src, nullptr);
				glCompileShader(id);
				
				int resualt;
				glGetShaderiv(id, GL_COMPILE_STATUS, &resualt);
				if (resualt == GL_FALSE)
				{
					int length;
					glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
					char* message = (char*)alloca(length * sizeof(char));
					glGetShaderInfoLog(id, length, &length, message);
					std::cout << "Failed to compile " << 
						(type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
						<< " shader!" << std::endl;
					std::cout << message << std::endl;
					glDeleteShader(id);
					return 0;
				}

				return id;
			}

			static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
			{
				unsigned int program = glCreateProgram();
				unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
				unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

				glAttachShader(program, vs);
				glAttachShader(program, fs);
				glLinkProgram(program);
				glValidateProgram(program);

				glDeleteShader(vs);
				glDeleteShader(fs);
			
				return program;
			}

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
			}

			void OpenGLRenderer::BackgroundColor(int color)
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

				unsigned int buffer;
				glGenBuffers(1, &buffer);
				glBindBuffer(GL_ARRAY_BUFFER, buffer);
				glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertecis, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

				float colors[4] =
				{
					(unsigned char)(color & 0xff) / 255.0f, 
					(unsigned char)((color >> (8)) & 0xff) / 255.0f, 
					(unsigned char)((color >> (16)) & 0xff) / 255.0f, 
					(unsigned char)((color >> (24)) & 0xff) / 255.0f
				};

				unsigned int colorBuffer;
				glGenBuffers(1, &colorBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
				glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), colors, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 1, 0);

				std::string vertexShader =
					"#version 330 core\n"
					"\n"
					"layout(location = 0) in vec4 position;\n"
					"\n"
					"void main()\n"
					"{\n"
					"	gl_Position = position;\n"
					"}\n";
				std::string fragmentShader =
					"#version 330 core\n"
					"\n"
					"layout(location = 0) out vec4 color;\n"
					// "layout(location = 1) in vec4 inColor;\n"
					"\n"
					"void main()\n"
					"{\n"
					"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
					"}\n";


				unsigned int shader = CreateShader(vertexShader, fragmentShader);
				glUseProgram(shader);
				std::cout << glGetError() << std::endl;
				switch (glGetError())
				{
				case GL_INVALID_ENUM:
					std::cout << "GL_INVALID_ENUM" << std::endl;
					break;
				case GL_INVALID_VALUE:
					std::cout << "GL_INVALID_VALUE" << std::endl;
					break;
				case GL_INVALID_OPERATION:
					std::cout << "GL_INVALID_OPERATION" << std::endl;
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
					break;
				case GL_OUT_OF_MEMORY:
					std::cout << "GL_OUT_OF_MEMORY" << std::endl;
					break;
				case GL_STACK_UNDERFLOW:
					std::cout << "GL_STACK_UNDERFLOW" << std::endl;
					break;
				case GL_STACK_OVERFLOW:
					std::cout << "GL_STACK_OVERFLOW" << std::endl;
					break;
				default:
					std::cout << "default" << std::endl;
					break;
				}
				

				glDrawArrays(GL_TRIANGLES, 0, 3);

			}
			// void DrawTriangle(Vector2 a, Vector2 b, Vector2 c, int color)
			// {

			// }

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