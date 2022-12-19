cmake_minimum_required(VERSION 3.0.0)
project(SolarSystem)
set(CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY}/libs/cmake)
#/home/ubuntu/SolarSystem
# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_LIBRARY_DIRS})

include_directories(.)

include(CTest)
enable_testing()

add_executable(SolarSystem main.cpp
    common/loadShader.cpp
    common/loadShader.hpp
    common/controls.cpp
    common/controls.hpp
    common/loadTexture.cpp
    common/loadTexture.hpp
    common/Shapes.cpp
    common/Shapes.hpp
    classes/Shader.hpp
    classes/Model.cpp
    classes/Model.hpp
    classes/Mesh.cpp
    classes/Mesh.hpp
    classes/Sphere.cpp
    classes/Sphere.hpp
    libs/stb_image.h
    libs/stb_image.cpp
    )

    
target_link_libraries(SolarSystem /usr/local/lib/libassimp.so)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

