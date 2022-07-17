# The Cherno OpenGL Tutorial

[YouTube Link](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)

[(Unofficial, but really nice) OpenGL Documentation](https://docs.gl)

## Table of Contents

- [Part 2](#part-2)
- [Part 3](#part-3)
- [Part 4](#part-4)
- [Part 5](#part-5)
- [Part 7](#part-7)
- [Part 8](#part-8)
- [Part 9](#part-9)
- [Part 10](#part-10)
- [Part 11](#part-11)
- [Part 12](#part-12)
- [Part 13](#part-13)
- [Part 14](#part-14)
- [Part 15](#part-15)
- [Part 16](#part-16)

### Part 2

Setting up OpenGL and Creating a Window in C++.

- Install GLFW
- Link GLFW and OpenGL to our program
- Draw a window using GLFW
- Draw a triangle using OpenGL

### Part 3

Using Modern OpenGL in C++

- Download and/or install GLEW
- Link GLEW to the program
- Initialize GLEW
- Print the version of OpenGL being used

### Part 4

Vertex Buffers and Drawing a Triangle in OpenGL

- Create a vertex buffer
- Invoke the draw call to draw the triangle (will not render without a shader)

### Part 5

Vertex Attributes and Layouts in OpenGL

- Specify the location and data format of the vertex buffer using `glVertexAttribPointer` (will make more sense once the shader is written)

### Part 7

Writing a Shader in OpenGL

- Write and compile a vertex shader
- Write and compile a fragment shader
- Link vertex and fragment shaders to a shader program

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

### Part 8

The Cherno's Way of Dealing with Shaders in OpenGL

- Move the vertex and fragment shader source code to a file
- Parse the shader file that contains vertex and fragment shader files to memory
- Pass the parsed shader code to the `createShader` method

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

### Part 9

Index Buffers in OpenGL

- Create an index buffer to prevent drawing duplicate vertices
- Use the index buffer (already bound) to draw the last bound position buffer using `glDrawElements`

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

### Part 10

Dealing with Errors in OpenGL

- Poll OpenGL for all errors that have occured
- Create a macro to stop the program once OpenGL throws an error
- Improve the macro to print the following
  - the function name
  - the file name
  - the line number
- wrap as many OpenGL function calls as possible (ideally, wrap all OpenGL calls)

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

### Part 11

Uniforms in OpenGL

- Create a uniform variable in the fragment shader code
- Set the shape's color by setting the uniform variable value in `application.cpp`
- Animate the shader's color over time

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

### Part 12

Vertex Arrays in OpenGL

- Create a vertex array and bind it before creating buffer arrays and shaders

**NOTE**: _Should_ render regardless of Core or Compatibility mode.

### Part 13

Abstracting OpenGL into Classes

- Abstract custom OpenGL methods and macros to `renderer` files
- Abstract the vertex buffer creation and binding in a class called `VertexBuffer`
- Abstract the index buffer creation and binding in a class called `IndexBuffer`
- Substitute all manual vertex buffer and index buffer code with class methods in `application.cpp`

### Part 14

Buffer Layout Abstraction in OpenGL

- Abstract Vertex Array Object interaction to separate class
- Abstract Vertex Buffer Object interaction to separate class
- Abstract defining Vertex Buffer layout to separate class
- Replace all vertex array code, vertex buffer code, and vertex layout code with the new classes to render a square

### Part 15

Shader Abstraction in OpenGL

- Abstract all shader creation and utilization code into a class called `Shader`.
- Use the `Shader` class in `application.cpp`

### Part 16

Writing a basic renderer in OpenGL

- Abstract the steps require to render the square in the render loop into the `Renderer` class
- Replace render code with the `Renderer` function calls
- Move the custom OpenGL logging calls to a separate file to prevent circular inclusion

### Part 17

Textures in OpenGL

- Copy the contents of [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) to `vendor/stb_image.h`
- create `vendor/stb_image.cpp` to do the proper imports for `vendor/stb_image.h`
- Create a texture class
- Find a PNG format of the logo of The Cherno's Youtube channel on google
- Create a texture instance in `application.cpp` and bind it to the shader
- update the `positions` im `application.cpp` to include texture binding coordinates
- update `resources/shaders/basic.shader` to render the texture
- enable blending and utilize a simple OpenGL blend method to make the logo less trashy

### Part 19

Maths in OpenGL

- Install the [GLM](https://github.com/g-truc/glm) libraries/source somehow
- create a projection matrix that's an orthogonal matrix
- create a uniform variable in the vertex shader to take the projection matrix
- add capability to set mat4 objects in `shader.h` and `shader.cpp`
