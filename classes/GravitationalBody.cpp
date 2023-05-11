#include <math.h>
#include <iostream>

#include "GravitationalBody.hpp"

GravitationalBody::GravitationalBody(float mass, glm::vec3 initPosition, glm::vec3 initVelocity){
    Mass = abs(mass);
    Position = initPosition;
    Velocity = initVelocity;
    ModelMat = glm::mat4(1.0f, 0.0f, 0.0f, Position.x,
                        0.0f, 1.0f, 0.0f, Position.y,
                        0.0f, 0.0f, 1.0f, Position.z,
                        0.0f, 0.0f, 0.0f, 1.0f);
}

void GravitationalBody::updatePosition(){

    Position = nextPosition;
    Velocity = nextVelocity;
    Acceleration = nextAcceleration;

    // recreate model matrix
    ModelMat = glm::mat4(1.0f, 0.0f, 0.0f, Position.x,
                        0.0f, 1.0f, 0.0f, Position.y,
                        0.0f, 0.0f, 1.0f, Position.z,
                        0.0f, 0.0f, 0.0f, 1.0f);
}

void GravitationalBody::DrawObject(Shader &shader){
    shader.use();
    shader.setMat("model", ModelMat);
    Draw(shader);
}