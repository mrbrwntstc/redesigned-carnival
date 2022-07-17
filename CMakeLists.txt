cmake_minimum_required(VERSION 3.11)
project(TheChernoOpenGLTutorial)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(src)
