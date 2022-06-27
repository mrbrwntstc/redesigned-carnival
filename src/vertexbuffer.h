#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

class VertexBuffer
{
private: // fields
  unsigned int m_rendererid;
  
public: // methods
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void bind() const;
  void unbind() const;

};

#endif //__VERTEX_BUFFER_H__