#ifndef Gravitational_H
#define Gravitational_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Sphere.hpp"

class GravitationalBody : public Sphere
{
    public:
        GravitationalBody(float Mass, glm::vec3 initPosition, glm::vec3 initVelocity);
        void updatePosition();

        float Mass;
        glm::vec3 Position, Velocity, Acceleration;
        glm::vec3 nextPosition, nextVelocity, nextAcceleration;
        glm::mat4 ModelMat;

        void DrawObject(Shader &shader); //! This is a placeholder, will work out better way once planet and moon classes are sorted
};

#endif