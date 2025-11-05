#pragma once

#include "VertexBuffer.h"

namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			class VertexBufferLayout;

			class VertexArray
			{
			private:
				unsigned int rendererID;
			public:
				VertexArray();
				~VertexArray();

				void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);

				void Bind() const;
				void Unbind() const;
			};
		}
	}
}