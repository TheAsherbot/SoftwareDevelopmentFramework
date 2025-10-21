#include "PreFramework.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Shader.h"


void Run()
{
	std::cout << "Hello World" << std::endl;
	GLFWwindow* window;

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


	window = glfwCreateWindow(300, 300, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Window or OpenGL context creation failed!" << std::endl;
		// Window or OpenGL context creation failed
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	GLenum glewStatus = glewInit();

	if (glewStatus != GLEW_OK)
	{
		std::cout << "GLEW FAILT TO INIT" << std::endl << glewGetErrorString(glewStatus) << std::endl;
	}
	else
	{
		std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	}

	// GL_CALL(glViewport(0, 0, 300, 300));

	GL_CALL(std::cout << glGetString(GL_VERSION) << std::endl);
	
	
	{

		float vertecis[8] =
		{
			-0.5, -0.5,
			-0.5,  0.5,
			 0.5,  0.5,
			 0.5, -0.5,
		};

		unsigned char indexBuffer[6]
		{
			0, 1, 2,
			0, 2, 3,
		};







		VertexArray vertexArray;

		VertexBuffer vertexBuffer(vertecis, 4 * 2 * sizeof(float));

		VertexBufferLayout vertexBufferLayout;
		vertexBufferLayout.Push<float>(2);

		vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);


		IndexBuffer indexBufferObject(indexBuffer, 6);


		Shader shader("Resources\\BasicVertex.shader", "Resources\\BasicFragment.shader");

		shader.Bind();
		shader.SetUniform4Float("u_Color", 0.1, 0.5, 0.1, 1.0);



		vertexArray.Unbind();
		shader.Unbind();
		vertexBuffer.Unbind();
		indexBufferObject.Unbind();

		float red = 0.0f;
		float increment = 0.05f;

		while (!glfwWindowShouldClose(window))
		{
			if (red < 0.0f)
			{
				increment = 0.02f;
			}
			else if (red > 1.0f)
			{
				increment = -0.02f;
			}
			red += increment;


			GL_CALL(glClearColor(1, 1, 0.5, 1));

			GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

			shader.Bind();
			shader.SetUniform4Float("u_Color", red, 0.3f, 0.8f, 1.0f);


			vertexArray.Bind();
			indexBufferObject.Bind();
			vertexBuffer.Bind();

			GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr));

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

 	glfwDestroyWindow(window);
 	glfwTerminate();
}
