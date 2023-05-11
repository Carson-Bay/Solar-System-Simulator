#ifndef SolarSystem_H
#define SolarSystem_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <math.h>

#include "GravitationalBody.hpp"

class SolarSystem 
{
    public:
        void updateObjects();
        vector<GravitationalBody> objects;
        
};

#endif
