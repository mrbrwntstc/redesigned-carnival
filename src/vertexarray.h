#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{
private: // fields
  unsigned int rendererid;

public: // methods
  VertexArray();
  ~VertexArray();

  void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

  void bind() const;
  void unbind() const;
};

#endif // __VERTEX_ARRAY_H__