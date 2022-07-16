#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "glerrorlogging.h"
#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.h"

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

  glfwSwapInterval(1); // only if v-sync is supported

  GLenum err = glewInit();
  if(GLEW_OK != err)
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;

  std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
  std::cout << "Status: Using OpenGL Version " << glGetString(GL_VERSION) << std::endl;

  float positions[16] = {
    -0.5f, -0.5f, 0.0f, 0.0f, // 0
    0.5f, -0.5f, 1.0f, 0.0f,  // 1
    //  0.5f,  0.5f,
    0.5f,  0.5f, 1.0f, 1.0f,  // 2
    -0.5f,  0.5f, 0.0f, 1.0f  // 3
    // -0.5f, -0.5f
  };

  unsigned int indices[6] = {
    0, 1, 2,
    2, 3, 0
  };

  GlCall(glEnable(GL_BLEND));
  GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  VertexArray va;
  VertexBuffer vb(positions, 4 * 4 * sizeof(float));

  VertexBufferLayout layout;
  layout.push<float>(2);
  layout.push<float>(2);
  va.addBuffer(vb, layout);

  IndexBuffer ib(indices, 6);

  Shader shader("/home/gbaby/repos/redesigned-carnival/resources/shaders/basic.shader");
  shader.bind();

  shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

  Texture texture("/home/gbaby/repos/redesigned-carnival/resources/textures/the_cherno_logo.png");
  texture.bind();
  shader.setUniform1i("u_texture", 0);

  // unbind everything
  va.unbind();
  vb.unbind();
  ib.unbind();
  shader.unbind();

  float r = 0.0f;
  float increment = 0.05f;

  Renderer renderer;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    renderer.clear();

    // GlCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    shader.bind();
    shader.setUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);

    renderer.draw(va, ib, shader);

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

  glfwTerminate();
  return 0;
}