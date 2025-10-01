#include "PreFramework.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


#define GL_CALL(x) GLClearLog();\
	x;\
	GLGetError(#x, __FILE__, __LINE__);

static void GLClearLog()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLGetError(const char* function, const char* file, int line)
{
	if (GLenum error = glGetError() != GL_NO_ERROR)
	{
		std::cout << "[OpenGL ERROR]: (" << error << "): " << function << ":" << line << " at\n" << file << std::endl;
		return true;
	}
	return false;
}


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


	window = glfwCreateWindow(300, 300, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Window or OpenGL context creation failed!" << std::endl;
		// Window or OpenGL context creation failed
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);


	GLenum glewStatus = glewInit();

	if (glewStatus != GLEW_OK)
	{
		std::cout << "GLEW FAILT TO INIT" << std::endl << glewGetErrorString(glewStatus) << std::endl;
	}
	else
	{
		std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	}

	GL_CALL(glViewport(0, 0, 300, 300));

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

	unsigned int buffer;
	GL_CALL(glGenBuffers(1, &buffer));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertecis) * sizeof(float), vertecis, GL_STATIC_DRAW));

	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));


	unsigned int indexBufferObject;
	GL_CALL(glGenBuffers(1, &indexBufferObject));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer) * sizeof(unsigned int), indexBuffer, GL_STATIC_DRAW));


	
	std::string vertexShader = ReadShader("Resources\\BasicVertex.shader");
	std::string fragmentShader = ReadShader("Resources\\BasicFragment.shader");

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	GL_CALL(glUseProgram(shader));

	GL_CALL(int colorLocation = glGetUniformLocation(shader, "u_Color"));
	GL_CALL(glUniform4f(colorLocation, 0.1, 0.5, 0.1, 1.0));
	

	while (!glfwWindowShouldClose(window))
	{
		GL_CALL(glClearColor(1, 1, 0.5, 1));

		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr));

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	
	GL_CALL(glDeleteProgram(shader));

	glfwDestroyWindow(window);
	glfwTerminate();
}