cmake_minimum_required(VERSION 3.11)
project(TheChernoOpenGLTutorial)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(src)
