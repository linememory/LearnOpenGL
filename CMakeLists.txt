cmake_minimum_required(VERSION 3.0)

project(Hello_Triangle)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glfw")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} src/main.cpp src/glad.c src/Shader.cpp)


target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
message(${OPENGL_INCLUDE_DIR})
