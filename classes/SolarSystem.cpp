#include "SolarSystem.hpp"

const float G = 1.0f; // !Placeholder, need to google actual value I may be a god and just remembered it

void SolarSystem::updateObjects() {  
    // glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);


    // TODO implement Verlet integration
    // Calculate Accelerations
    for(int index=0;index<objects.size();index++) {
        objects[index].Acceleration = glm::vec3(0.0f,0.0f,0.0f);
        for(int j=0;j<objects.size();j++){
            // Only calculate for other objects
            if(j != index){
                glm::vec3 radius = objects[j].Position - objects[index].Position;
                glm::vec3 r2(pow(radius.x,2),pow(radius.y,2),pow(radius.z,2));
                objects[index].Acceleration -= G *objects[j].Mass*objects[index].Mass/r2;
            }
        }
    }
    // Update Velocities and Positions
    for(int index=0;index<objects.size();index++) {
        objects[index].updatePosition(deltaTime);
    }

    lastTime = currentTime;
}