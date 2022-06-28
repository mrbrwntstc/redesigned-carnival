#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"

class Renderer
{
private: // fields
public: // methods
  void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
  void clear() const;
};

#endif // __RENDERER_H__