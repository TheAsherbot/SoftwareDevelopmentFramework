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

static std::string ReadShader(std::string path)
{
	std::ifstream stream(path);

	std::string shader = "";
	std::string line = "";
	
	while (getline(stream, line))
	{
		if (line.find("VERTEX SHADER") != std::string::npos || line.find("FRAGMENT SHADER") != std::string::npos)
		{
			continue;
		}

		shader += line + '\n';

	}

	return shader;
}

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
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
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

	


	unsigned int vertexArrayObject;
	GL_CALL(glGenVertexArrays(1, &vertexArrayObject));
	GL_CALL(glBindVertexArray(vertexArrayObject));


 
 	VertexBuffer vertexBuffer(vertecis, 4 * 2 * sizeof(float));
 
 
 
 
 	GL_CALL(glEnableVertexAttribArray(0));
 	GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
 
 
 	IndexBuffer indexBufferObject(indexBuffer, 6);
 
 
 	std::string vertexShader = ReadShader("Resources\\BasicVertex.shader");
 	std::string fragmentShader = ReadShader("Resources\\BasicFragment.shader");
 
 	unsigned int shader = CreateShader(vertexShader, fragmentShader);
 	GL_CALL(glUseProgram(shader));
 
 	GL_CALL(int colorLocation = glGetUniformLocation(shader, "u_Color"));
 	GL_CALL(glUniform4f(colorLocation, 0.1, 0.5, 0.1, 1.0));
 
 
 	GL_CALL(glBindVertexArray(0));
 	GL_CALL(glUseProgram(0));
 	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
 	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
 
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
		std::cout << "increment: " << increment << std::endl;
		std::cout << "red: " << red << std::endl;
 
 
 		GL_CALL(glClearColor(1, 1, 0.5, 1));
 
 		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
 
 		GL_CALL(glUseProgram(shader));
 		GL_CALL(glUniform4f(colorLocation, red, 0.3f, 0.8f, 1.0f));
 
 
 		GL_CALL(glBindVertexArray(vertexArrayObject));
		indexBufferObject.Bind();
		vertexBuffer.Bind();
 
 		GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr));
 
 		glfwSwapBuffers(window);
 
 		glfwPollEvents();
 	}
 
 	GL_CALL(glDeleteProgram(shader));
 
 	glfwDestroyWindow(window);
 	glfwTerminate();
}