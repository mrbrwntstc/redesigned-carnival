# inherited everything from parent CMakeLists.txt

set(SOURCE_FILES
  application.cpp
  indexbuffer.h indexbuffer.cpp
  vertexbuffer.h vertexbuffer.cpp
  renderer.h renderer.cpp
  vertexarray.h vertexarray.cpp
  vertexbufferlayout.h
  shader.h shader.cpp
  renderer.h renderer.cpp
  glerrorlogging.h glerrorlogging.cpp
  vendor/stb_image.h vendor/stb_image.cpp
  texture.h texture.cpp
)

add_executable(thechernopengl ${SOURCE_FILES})

target_compile_definitions(thechernopengl
PRIVATE
  GLEW_STATIC
)

target_include_directories(thechernopengl
PRIVATE
  ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(thechernopengl
PRIVATE
  glfw
  OpenGL::GL
  ${GLEW_LIBRARIES}
)
