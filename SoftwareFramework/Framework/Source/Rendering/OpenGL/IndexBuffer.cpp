#include "IndexBuffer.h"

#include "OpenGLHelper.h"
#include <GLEW/glew.h>
namespace Framework
{
    namespace Rendering
    {
        namespace OpenGl
        {
            IndexBuffer::IndexBuffer(const unsigned char* data, unsigned int count) : count(count)
            {
                GL_CALL(glGenBuffers(1, &rendererID));
                GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
                GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned char), data, GL_STATIC_DRAW));
            }

            IndexBuffer::~IndexBuffer()
            {
                GL_CALL(glDeleteBuffers(1, &rendererID))
            }

            void IndexBuffer::Bind() const
            {
                GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
            }

            void IndexBuffer::Unbind() const
            {
                GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            }
        }
    }
}