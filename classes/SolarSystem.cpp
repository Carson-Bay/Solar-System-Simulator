#include "SolarSystem.hpp"

const float G = 6.67E-6; //6.67E-11; I was a god and just remebered it 
float maxDeltaTime = 1 / 60.0; 
#define __min(a,b) (((a) < (b)) ? (a) : (b))

using namespace glm;

void SolarSystem::updateObjects() {  
    // glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);  
  deltaTime = __min(deltaTime, maxDeltaTime);

    // Velocity Verlet
    // get next positions
    for(int index=0; index<objects.size(); index++) {
        vec3 x = objects[index].Position;
        vec3 v = objects[index].Velocity;
        vec3 a = objects[index].Acceleration;

        objects[index].nextPosition = x + v*deltaTime + a*deltaTime*deltaTime*0.5f;
    }

    // Next Velocity and Acceleration
    for(int index=0; index<objects.size(); index++) {
        // Reset acceleration
        objects[index].nextAcceleration = glm::vec3(0.0f,0.0f,0.0f);
        // Add acceleration components from each other object
        for(int j=0;j<objects.size();j++){
            // Only calculate for other objects
            if(j != index){
                glm::vec3 radius = objects[j].nextPosition - objects[index].nextPosition;
                float radiusSquared = (pow(radius.x, 2) + pow(radius.y, 2) + pow(radius.z, 2));
                objects[index].nextAcceleration += (G *objects[j].Mass/radiusSquared)*radius;
            }
        }
        objects[index].nextVelocity = objects[index].Velocity + (objects[index].Acceleration + objects[index].nextAcceleration)*deltaTime*0.5f;
    }
    // Update to next timestep
    for(int index=0;index<objects.size();index++) {
        objects[index].updatePosition();
    }

    lastTime = currentTime;
}
