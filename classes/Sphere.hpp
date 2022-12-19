#ifndef Sphere_H
#define Sphere_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"

using namespace std;

class Sphere : public Model
{
    public:
        Sphere();
        void genUVs();
    private:

};


#endif