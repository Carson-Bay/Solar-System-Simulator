#ifndef Shapes_h
#define Shapes_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h>

#include "../classes/Mesh.hpp"

Mesh octahedron();

vector<Mesh> subdivideTriangles(Mesh mesh, uint32_t resolution);
#endif