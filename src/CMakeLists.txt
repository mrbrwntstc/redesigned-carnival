# inherited everything from parent CMakeLists.txt

set(SOURCE_FILES
  application.cpp
)

add_executable(thechernopengl ${SOURCE_FILES})

target_link_libraries(thechernopengl
PRIVATE
  glfw
  OpenGL::GL
)
