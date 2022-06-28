#include "shader.h"
#include "glerrorlogging.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Shader::Shader(const std::string& filename)
  : filepath(filename), rendererid(0)
{
  ShaderProgramSource source = parseShader(this->filepath);
  this->rendererid = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
  GlCall(glDeleteProgram(this->rendererid));
}

void Shader::bind() const
{
  GlCall(glUseProgram(this->rendererid));
}

void Shader::unbind() const
{
  GlCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
  GlCall(glUniform4f(this->getUniformLocation(name), f0, f1, f2, f3));
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
  if(this->uniformCache.find(name) != this->uniformCache.end())
    return this->uniformCache[name];

  GlCall(int location = glGetUniformLocation(this->rendererid, name.c_str()));
  if(location == -1)
    std::cout << "Warning: uniform " << location << " does not exist";

  this->uniformCache[name] = location;
  
  return location;
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
  std::ifstream stream(filepath);

  enum class ShaderType
  {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;
  while(getline(stream, line))
  {
    if(line.find("#shader") != std::string::npos)
    {
      if(line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if(line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    }
    else
    {
      ss[(int)type] << line << '\n';
    }
  }

  return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
  GlCall(unsigned int id = glCreateShader(type));
  const char* src = source.c_str();
  GlCall(glShaderSource(id, 1, &src, nullptr));
  GlCall(glCompileShader(id));

  int result;
  GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if(result == GL_FALSE)
  {
    int length;
    GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char message[length];
    // char* message = (char*)alloca(length * sizeof(char)); // dynamically allocate memory on the stack
    GlCall(glGetShaderInfoLog(id, length, &length, message));
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
    std::cout << message << std::endl;
    GlCall(glDeleteShader(id));
    return 0;
  }

  return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}
