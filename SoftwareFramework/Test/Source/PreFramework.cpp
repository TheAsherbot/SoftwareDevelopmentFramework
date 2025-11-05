#include "PreFramework.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Vendor/glm/glm.hpp"
#include "Vendor/glm/gtc/matrix_transform.hpp"

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Shader.h"

#include "Texture.h"



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


	window = glfwCreateWindow(720, 480, "Hello World", NULL, NULL);
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

	GL_CALL(std::cout << glGetString(GL_VERSION) << std::endl);
	
	
	{

		float vertecis[16] =
		{
			0.0f,   0.0f, 0.0f, 0.0f,
			0.0f,   320.0f, 0.0f, 1.0f,
			240.0f, 320.0f, 1.0f, 1.0f,
			240.0f, 0.0f, 1.0f, 0.0f
		};

		unsigned char indexBuffer[6]
		{
			0, 1, 2,
			0, 2, 3,
		};


		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));




		VertexArray vertexArray;

		VertexBuffer vertexBuffer(vertecis, 4 * 4 * sizeof(float));

		VertexBufferLayout vertexBufferLayout;
		vertexBufferLayout.Push<float>(2);
		vertexBufferLayout.Push<float>(2);

		vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);


		IndexBuffer indexBufferObject(indexBuffer, 6);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
		glm::mat4 projection = glm::ortho(0.0f, 720.0f, 0.0f, 480.0f, -1.0f, 1.0f);

		glm::mat4 modelViewProjection = projection * view * model;

		Shader shader("Resources\\BasicVertex.shader", "Resources\\BasicFragment.shader");

		shader.Bind();
		shader.SetUniform4Float("u_Color", 0.1, 0.5, 0.1, 1.0);
		shader.SetUniformMatrix4Float("u_ModelViewProjection", modelViewProjection);


		Texture texture1("Resources/image1.jpg");
		texture1.Bind(1);
		Texture texture0("Resources/image0.png");
		texture0.Bind(0);

		shader.SetUniform1Int("u_Texture", 0);


		vertexArray.Unbind();
		shader.Unbind();
		vertexBuffer.Unbind();
		indexBufferObject.Unbind();

		float red = 0.0f;
		float increment = 0.05f;

		Renderer renderer;

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

			renderer.SetBackground(255, 255, 128);

			renderer.Clear();

			shader.Bind();
			shader.SetUniform4Float("u_Color", red, 0.3f, 0.8f, 1.0f);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
			texture1.Bind(1);
			shader.SetUniform1Int("u_Texture", 1);
			modelViewProjection = projection * view * model;
			shader.SetUniformMatrix4Float("u_ModelViewProjection", modelViewProjection);
			vertexArray.Bind();
			indexBufferObject.Bind();
			vertexBuffer.Bind();
			renderer.Draw(vertexArray, indexBufferObject, shader);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 50, 0));
			texture0.Bind(0);
			shader.SetUniform1Int("u_Texture", 0);
			modelViewProjection = projection * view * model;
			shader.SetUniformMatrix4Float("u_ModelViewProjection", modelViewProjection);
			vertexArray.Bind();
			indexBufferObject.Bind();
			vertexBuffer.Bind();
			renderer.Draw(vertexArray, indexBufferObject, shader);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

 	glfwDestroyWindow(window);
 	glfwTerminate();
}
