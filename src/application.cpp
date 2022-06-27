#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x) if(!(x)) __builtin_trap()
#define GlCall(x) GlClearError();\
  x;\
  ASSERT(GlLogCall(#x, __FILE__, __LINE__))

static void GlClearError()
{
  while(glGetError() != GL_NO_ERROR);
}

static bool  GlLogCall(const char* function, const char* file, int line)
{
  while(GLenum error = glGetError())
  {
    std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
    return false;
  }

  return true;
}

struct ShaderProgramSource
{
  std::string vertexSource;
  std::string fragmentSource;
};

static ShaderProgramSource parseShader(const std::string& path)
{
  std::ifstream stream(path);

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

static unsigned int compileShader(unsigned int type, const std::string& source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char message[length];
    // char* message = (char*)alloca(length * sizeof(char)); // dynamically allocate memory on the stack
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
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

int main(void)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  // hint at OpenGL to use modern OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if(GLEW_OK != err)
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;

  std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
  std::cout << "Status: Using OpenGL Version " << glGetString(GL_VERSION) << std::endl;

  float positions[8] = {
    -0.5f, -0.5f,     // 0
     0.5f, -0.5f,     // 1
    //  0.5f,  0.5f,
     0.5f,  0.5f,     // 2
    -0.5f,  0.5f      // 3
    // -0.5f, -0.5f
  };

  unsigned int indices[6] = {
    0, 1, 2,
    2, 3, 0
  };

  unsigned int vao;
  GlCall(glGenVertexArrays(1, &vao));
  GlCall(glBindVertexArray(vao));

  unsigned int buffer;
  GlCall(glGenBuffers(1, &buffer));
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
  GlCall(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

  GlCall(glEnableVertexAttribArray(0));
  GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));


  unsigned int ibo; // index buffer object
  GlCall(glGenBuffers(1, &ibo));
  GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
  GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

  ShaderProgramSource source = parseShader("/home/mrbrwntstc/repos/redesigned-carnival/resources/shaders/basic.shader");
  // std::cout << "VERTEX" << std::endl;
  // std::cout << source.vertexSource << std::endl;
  // std::cout << "FRAGMENT" << std::endl;
  // std::cout << source.fragmentSource << std::endl;
  unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
  GlCall(glUseProgram(shader));

  GlCall(int location = glGetUniformLocation(shader, "u_color"));
  ASSERT(location != -1);
  GlCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

  // unbind everything
  GlCall(glBindVertexArray(0));
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GlCall(glUseProgram(0));

  float r = 0.0f;
  float increment = 0.05f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    GlCall(glClear(GL_COLOR_BUFFER_BIT));

    GlCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, ibo));
    GlCall(glUseProgram(shader));  

    GlCall(glBindVertexArray(vao));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

    // glDrawArrays(GL_TRIANGLES, 0, 6); // no index buffer
    GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // with index buffer
    // GlCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr)); // wrong(?)

    if(r > 1.0f)
      increment = -0.05f;
    else if(r < 0.0f)
      increment = 0.05f;

    r += increment;

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  GlCall(glDeleteProgram(shader));

  glfwSwapInterval(1);

  glfwTerminate();
  return 0;
}