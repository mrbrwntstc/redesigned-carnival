#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
  std::string vertexSource;
  std::string fragmentSource;
};

class Shader
{
private: //fields
  unsigned int rendererid;
  std::string filepath;
  // caching for uniforms
  std::unordered_map<std::string, int> uniformCache;

private: // methods
  unsigned int getUniformLocation(const std::string& name);
  bool compileShader();
  unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
  unsigned int compileShader(unsigned int type, const std::string& source);
  ShaderProgramSource parseShader(const std::string& filepath);

public: // methods
  Shader(const std::string& filename);
  ~Shader();

  void bind() const;
  void unbind() const;

  // set uniforms
  void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
};

#endif // __SHADER_H__