#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>

#include <GLFW/glfw3.h>


// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);
GLuint loadBMP_custom(const char * imagepath);

#endif