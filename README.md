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

<br>

### Part 2
----------
Setting up OpenGL and Creating a Window in C++.

+ Install GLFW
+ Link GLFW and OpenGL to our program
+ Draw a window using GLFW
+ Draw a triangle using OpenGL

<br>

### Part 3
----------
Using Modern OpenGL in C++

+ Download and/or install GLEW
+ Link GLEW to the program
+ Initialize GLEW
+ Print the version of OpenGL being used

<br>

### Part 4
----------
Vertex Buffers and Drawing a Triangle in OpenGL

+ Create a vertex buffer
+ Invoke the draw call to draw the triangle (will not render without a shader)

<br>

### Part 5
----------
Vertex Attributes and Layouts in OpenGL

+ Specify the location and data format of the vertex buffer using `glVertexAttribPointer` (will make more sense once the shader is written)

<br>

### Part 7
----------
Writing a Shader in OpenGL

+ Write and compile a vertex shader
+ Write and compile a fragment shader
+ Link vertex and fragment shaders to a shader program

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

<br>

### Part 8
----------
The Cherno's Way of Dealing with Shaders in OpenGL

+ Move the vertex and fragment shader source code to a file
+ Parse the shader file that contains vertex and fragment shader files to memory
+ Pass the parsed shader code to the `createShader` method

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

<br>

### Part 9
----------
Index Buffers in OpenGL

+ Create an index buffer to prevent drawing duplicate vertices
+ Use the index buffer (already bound) to draw the last bound position buffer using `glDrawElements`

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

<br>

### Part 10
-----------
Dealing with Errors in OpenGL

+ Poll OpenGL for all errors that have occured
+ Create a macro to stop the program once OpenGL throws an error
+ Improve the macro to print the following
  - the function name
  - the file name
  - the line number
+ wrap as many OpenGL function calls as possible (ideally, wrap all OpenGL calls)

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

### Part 11
-----------
Uniforms in OpenGL

+ Create a uniform variable in the fragment shader code
+ Set the shape's color by setting the uniform variable value in `application.cpp`
+ Animate the shader's color over time

**NOTE**: If OpenGL Compatibility mode, should render. If OpenGL Core mode, won't render.

### Part 12
-----------
Vertex Arrays in OpenGL

+ Create a vertex array and bind it before creating buffer arrays and shaders

**NOTE**: _Should_ render regardless of Core or Compatibility mode.

### Part 13
-----------
Abstracting OpenGL into Classes

+ Abstract custom OpenGL methods and macros to `renderer` files
+ Abstract the vertex buffer creation and binding in a class called `VertexBuffer`
+ Abstract the index buffer creation and binding in a class called `IndexBuffer`
+ Substitute all manual vertex buffer and index buffer code with class methods in `application.cpp`
