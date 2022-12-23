#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#include "Sphere.hpp"
#include "../common/Shapes.hpp"


Sphere::Sphere(){
    Mesh oct = octahedron();
    meshes = subdivideTriangles(oct, 20);
    for(int i =0; i<meshes.size(); i++){
        meshes[i].mapToSphere();
        meshes[i].genSphereUVs();
    }
}

