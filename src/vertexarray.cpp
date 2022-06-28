#include "vertexarray.h"
#include "glerrorlogging.h"

VertexArray::VertexArray()
{
  GlCall(glGenVertexArrays(1, &this->rendererid));
  GlCall(glBindVertexArray(this->rendererid));
}

VertexArray::~VertexArray()
{
  GlCall(glDeleteVertexArrays(1, &this->rendererid));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
  this->bind();
  vb.bind();

  const auto& elements = layout.getElements();
  unsigned int offset = 0;
  for(unsigned int i = 0; i < elements.size(); i++)
  {
    const auto& element = elements[i];
    GlCall(glEnableVertexAttribArray(i));
    GlCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
    offset += element.count * VertexBufferElement::getAttributeSize(element.type);
  }
}

void VertexArray::bind() const
{
  GlCall(glBindVertexArray(this->rendererid));
}

void VertexArray::unbind() const
{
  GlCall(glBindVertexArray(0));
}
