#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << ' ' << file << ':' << line << std::endl;
        return false;
    }
    return true;
}


void Renderer::Clear() const
{
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
    shader.Bind();
    vertexArray.Bind();
    indexBuffer.Bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_BYTE, nullptr));
}

void Renderer::SetBackground(unsigned char r, unsigned char g, unsigned char b)
{
    GL_CALL(glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1));
}
