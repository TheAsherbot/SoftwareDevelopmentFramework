#pragma once

#include <string>
#include <unordered_map>

#include "Vendor/glm/glm.hpp"


namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			class Shader
			{
			private:
				std::string fragmentFilePath;
				std::string vertexFilePath;
				unsigned int rendererID;
				std::unordered_map<std::string, int> uniformLocationCache;
			public:

				Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
				~Shader();


				void Bind() const;
				void Unbind() const;

				// Set Uniforms
				void SetUniform1Int(const std::string& name, int value);
				void SetUniform1Float(const std::string& name, float value);
				void SetUniform4Float(const std::string& name, float value0, float value1, float value2, float value3);
				void SetUniformMatrix4Float(const std::string& name, const glm::mat4& matrix);
			private:
				std::string ParseShader(const std::string& filePath);
				unsigned int CompileShader(unsigned int type, const std::string& source);
				unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

				int GetUniformLocation(const std::string& name);
			};
		}
	}
}