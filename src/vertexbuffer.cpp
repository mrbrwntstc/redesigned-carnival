#include "vertexbuffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
  GlCall(glGenBuffers(1, &this->m_rendererid));
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_rendererid));
  GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
  GlCall(glDeleteBuffers(1, &this->m_rendererid));
}

void VertexBuffer::bind() const
{
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_rendererid));
}

void VertexBuffer::unbind() const
{
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}