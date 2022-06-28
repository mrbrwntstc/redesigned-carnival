#include "renderer.h"
#include "glerrorlogging.h"

#include <iostream>

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
  shader.bind();
  va.bind();
  ib.bind();

  GlCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
  GlCall(glClear(GL_COLOR_BUFFER_BIT));
}
