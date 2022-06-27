#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __builtin_trap()
#define GlCall(x) GlClearError();\
  x;\
  ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void GlClearError();
bool  GlLogCall(const char* function, const char* file, int line);


#endif // __RENDERER_H__