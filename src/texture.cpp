#include "texture.h"
#include "vendor/stb_image.h"

Texture::Texture(const std::string& path) 
  : _rendererid(0), _filepath(path), _localbuffer(nullptr), _width(0), _height(0), _bpp(0)
{
  stbi_set_flip_vertically_on_load(1);
  _localbuffer = stbi_load(path.c_str(), &_width, &_height, &_bpp, 4 /* RGBA */);
  GlCall(glGenTextures(1, &_rendererid));
  GlCall(glBindTexture(GL_TEXTURE_2D, _rendererid));

  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // texture horizontal axis
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  // texture vertical axis
  GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localbuffer));
  GlCall(glBindTexture(GL_TEXTURE_2D, 0));

  if(_localbuffer)
    stbi_image_free(_localbuffer);
}

Texture::~Texture() {
  GlCall(glDeleteTextures(1, &_rendererid));
}

void Texture::bind(unsigned int slot) const {
  GlCall(glActiveTexture(GL_TEXTURE0 + slot));
  GlCall(glBindTexture(GL_TEXTURE_2D, _rendererid));
}
void Texture::unbind() const { GlCall(glBindTexture(GL_TEXTURE_2D, 0)); }
