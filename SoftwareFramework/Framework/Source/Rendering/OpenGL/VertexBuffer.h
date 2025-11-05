#pragma once


namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			class VertexBuffer
			{
			private:
				unsigned int rendererID;

			public:
				VertexBuffer(const void* data, unsigned int size);
				~VertexBuffer();

				void Bind() const;
				void Unbind() const;
			};
		}
	}
}