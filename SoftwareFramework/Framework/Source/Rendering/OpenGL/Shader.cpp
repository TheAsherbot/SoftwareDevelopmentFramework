#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLEW/glew.h>

#include "OpenGLHelper.h"

namespace Framework
{
    namespace Rendering
    {
        namespace OpenGl
        {
            Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
                : vertexFilePath(vertexFilePath), fragmentFilePath(fragmentFilePath), rendererID(0)
            {
                rendererID = CreateShader(ParseShader(vertexFilePath), ParseShader(fragmentFilePath));
            }

            Shader::~Shader()
            {
                GL_CALL(glDeleteProgram(rendererID));
            }

            std::string Shader::ParseShader(const std::string& filePath)
            {
                std::ifstream stream(filePath);

                if (stream.fail())
                {
                    std::cout << "ERROR: cant not find path \'" << filePath << "\'. " << std::endl;
                }

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


            unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
            {
                GL_CALL(unsigned int id = glCreateShader(type));
                const char* sourceChar = source.c_str();
                GL_CALL(glShaderSource(id, 1, &sourceChar, nullptr));
                GL_CALL(glCompileShader(id));

                int result;
                GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
                if (result == GL_FALSE)
                {
                    int length;
                    GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
                    char* message = (char*)alloca(length * sizeof(char));
                    GL_CALL(glGetShaderInfoLog(id, length, &length, message));
                    std::cout << "ERROR: Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
                    std::cout << message << std::endl;
                    GL_CALL(glDeleteShader(id));
                    return 0;
                }

                return id;
            }

            unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
            {
                GL_CALL(unsigned int program = glCreateProgram());
                unsigned int vertexShaderIndex = CompileShader(GL_VERTEX_SHADER, vertexShader);
                unsigned int fragmentShaderIndex = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

                GL_CALL(glAttachShader(program, vertexShaderIndex));
                GL_CALL(glAttachShader(program, fragmentShaderIndex));
                GL_CALL(glLinkProgram(program));
                GL_CALL(glValidateProgram(program));

                GL_CALL(glDeleteShader(vertexShaderIndex));
                GL_CALL(glDeleteShader(fragmentShaderIndex));

                return program;
            }


            void Shader::Bind() const
            {
                GL_CALL(glUseProgram(rendererID));
            }

            void Shader::Unbind() const
            {
                GL_CALL(glUseProgram(0));
            }

            void Shader::SetUniform1Int(const std::string& name, int value)
            {
                GL_CALL(glUniform1i(GetUniformLocation(name), value));
            }

            void Shader::SetUniform1Float(const std::string& name, float value)
            {
                GL_CALL(glUniform1f(GetUniformLocation(name), value));
            }

            void Shader::SetUniform4Float(const std::string& name, float value0, float value1, float value2, float value3)
            {
                GL_CALL(glUniform4f(GetUniformLocation(name), value0, value1, value2, value3));
            }


            void Shader::SetUniformMatrix4Float(const std::string& name, const glm::mat4& matrix)
            {
                GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
            }


            int Shader::GetUniformLocation(const std::string& name)
            {
                if (uniformLocationCache.find(name) != uniformLocationCache.end())
                    return uniformLocationCache[name];

                GL_CALL(int location = glGetUniformLocation(rendererID, name.c_str()));
                if (location == -1)
                {
                    std::cout << "Warning: uniform '" << name << "' does not exist!" << std::endl;
                }

                uniformLocationCache[name] = location;
                return location;
            }

        }
    }
}