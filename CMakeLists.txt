cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(Lighting)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} src/main.cpp src/glad.c src/Shader.cpp src/Camera.cpp src/Mesh.cpp)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glfw")
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/assimp")
target_link_libraries(${PROJECT_NAME} assimp)

#target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
message(STATUS ${OPENGL_INCLUDE_DIR})

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_custom_target(copy-runtime-files ALL
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
    DEPENDS ${MY_TARGET})

