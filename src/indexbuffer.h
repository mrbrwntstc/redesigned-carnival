#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

class IndexBuffer
{
private: // fields
  unsigned int m_rendererid;
  unsigned int m_count;
  
public: // methods
  IndexBuffer(const unsigned int* data, unsigned int count);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;


  inline unsigned int getCount() const { return this->m_count; }
};

#endif //__INDEX_BUFFER_H__