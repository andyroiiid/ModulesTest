cmake_minimum_required(VERSION 3.25)
project(ModulesTest)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(glfw EXCLUDE_FROM_ALL)

add_subdirectory(glad EXCLUDE_FROM_ALL)

add_executable(ModulesTest Main.ixx Window.ixx Shader.ixx VertexBuffer.ixx Movable.ixx)

target_compile_definitions(ModulesTest PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(ModulesTest PRIVATE glfw glad)
