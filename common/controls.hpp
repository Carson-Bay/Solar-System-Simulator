#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 getProjectionMatrix();
glm::mat4 getViewMatrix();
glm::vec3 getCameraPosition();