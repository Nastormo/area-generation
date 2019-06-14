cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Camera.h
        Camera.cpp
        ShaderProgram.h
        ShaderProgram.cpp
        common.h)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

add_executable(main ${SOURCE_FILES})
target_link_libraries(main ${OPENGL_gl_LIBRARY} glfw GLEW)
add_custom_command(TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/shaders" "${PROJECT_BINARY_DIR}")