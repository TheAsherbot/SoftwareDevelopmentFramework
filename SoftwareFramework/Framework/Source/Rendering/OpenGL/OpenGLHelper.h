#pragma once

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_CALL(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__));

			void GLClearError();
			bool GLLogCall(const char* function, const char* file, int line);
		}
	}
}