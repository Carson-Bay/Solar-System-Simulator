cmake_minimum_required(VERSION 3.0.0)
project(SolarSystem)

# OpenGL
find_package(OpenGL REQUIRED)

# GLM
set(GLM_INCLUDE_DIR "C:/OpenGL/GLM")
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
set(GLFW3_INCLUDE_DIR "C:/OpenGL/GLFW/include")
set(GLFW3_LIBRARY_DIR "C:/msys64/mingw64/lib/libglfw3.a")
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# GLEW
set(GLEW_INCLUDE_DIR  "C:/msys64/home/cgbma/glew-2.1.0/include")
set(GLEW_LIBRARY_DIR  "C:/msys64/home/cgbma/glew-2.1.0/lib/libglew32.a")

find_package(GLEW REQUIRED)

include(CTest)
enable_testing()

add_executable(SolarSystem main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    ${GLEW_LIBRARY_DIR}
    ${GLFW3_LIBRARY_DIR})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${GLM_INCLUDE_DIR}
    PUBLIC ${GLFW_INCLUDE_DIR}
    PUBLIC ${GLEW_INCLUDE_DIR})

