# The Cherno OpenGL Tutorial

[YouTube Link](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)

[OpenGL Documentation](https://docs.gl)

## Table of Contents
- [Part 2](#part-2)
- [Part 3](#part-3)
- [Part 4](#part-4)
- [Part 5](#part-5)
- [Part 7](#part-7)
- [Part 8](#part-8)

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

**NOTE**: May or may not draw since there's no vertex array buffer and vertex buffer object

<br>

### Part 8
----------
The Cherno's Way of Dealing with Shaders in OpenGL

+ Move the vertex and fragment shader source code to a file
+ Parse the shader file that contains vertex and fragment shader files to memory
+ Pass the parsed shader code to the `createShader` method
