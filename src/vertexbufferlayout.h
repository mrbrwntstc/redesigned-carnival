#ifndef __VERTEX_BUFFER_LAYOUT_H__
#define __VERTEX_BUFFER_LAYOUT_H__

#include <vector>
#include <GL/glew.h>

#include "renderer.h"

struct VertexBufferElement
{
  unsigned int count;
  unsigned int type;
  unsigned int normalized;

  static unsigned int getAttributeSize(unsigned int type)
  {
    switch(type)
    {
      case GL_FLOAT:
        return sizeof(GLfloat);
        break;
      case GL_UNSIGNED_INT:
        return sizeof(GLuint);
        break;
      case GL_UNSIGNED_BYTE:
        return sizeof(GLchar);
        break;
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout
{
private: // fields
  std::vector<VertexBufferElement> elements;
  unsigned int stride;

public: // methods
  VertexBufferLayout()
    : stride(0) {}

  template<typename T>
  void push(unsigned int count);

  inline const std::vector<VertexBufferElement>& getElements() const { return this->elements; }
  inline unsigned int getStride() const { return this->stride; }
};

template<>
inline void VertexBufferLayout::push<float>(unsigned int count)
{
  this->elements.push_back({ count, GL_FLOAT, GL_FALSE });
  this->stride += VertexBufferElement::getAttributeSize(GL_FLOAT) * count;
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
  this->elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
  this->stride += VertexBufferElement::getAttributeSize(GL_UNSIGNED_INT) * count;
}

template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
  this->elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
  this->stride += VertexBufferElement::getAttributeSize(GL_UNSIGNED_BYTE) * count;
}

#endif // __VERTEX_BUFFER_LAYOUT_H__