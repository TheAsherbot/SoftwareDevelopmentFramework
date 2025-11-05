#pragma once


namespace Framework
{
	namespace Rendering
	{
		namespace OpenGl
		{
			class IndexBuffer
			{
			private:
				unsigned int rendererID;
				unsigned int count;

			public:
				IndexBuffer(const unsigned char* data, unsigned int count);
				~IndexBuffer();

				void Bind() const;
				void Unbind() const;

				inline unsigned int GetCount() const { return count; }
			};
		}
	}
}