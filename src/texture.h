#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "renderer.h"

class Texture
{
private: // fields
  unsigned int _rendererid;
  std::string _filepath;
  unsigned char *_localbuffer;
  int _width, _height, _bpp;

public: // methods
  Texture(const std::string& path);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind() const;

  inline int getWidth() const { return _width; }
  inline int getHeight() const { return _height; }
};

#endif // __TEXTURE_H__
