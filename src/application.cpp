#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"

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

  VertexArray va;
  VertexBuffer vb(positions, 4 * 2 * sizeof(float));
  VertexBufferLayout layout;
  layout.push<float>(2);
  va.addBuffer(vb, layout);

  IndexBuffer ib(indices, 6);

  Shader shader("/home/mrbrwntstc/repos/redesigned-carnival/resources/shaders/basic.shader");
  shader.bind();

  shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

  // unbind everything
  va.unbind();
  vb.unbind();
  ib.unbind();
  shader.unbind();

  float r = 0.0f;
  float increment = 0.05f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    GlCall(glClear(GL_COLOR_BUFFER_BIT));

    // GlCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    shader.bind();
    shader.setUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);

    va.bind();
    ib.bind();

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

  glfwTerminate();
  return 0;
}