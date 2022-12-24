#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>

#include "controls.hpp"

using namespace std;

// position
glm::vec3 position = glm::vec3( 0, 0, 20 );
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float epsilon = 0.01f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

void computeMatricesFromInputs(GLFWwindow* window){
    // glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

    int width, height;
    glfwGetWindowSize(window, &width, &height);


	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction = glm::normalize(-position);
	
	// Up vector
	glm::vec3 posY(0,1,0);
	glm::vec3 rotationAxis = glm::cross(direction, posY);
	glm::quat upRotationQuat = glm::angleAxis(glm::degrees(3.14f/2.0f), rotationAxis);
	glm::mat4 upRotationMat = glm::toMat4(upRotationQuat);
	glm::vec3 up = glm::normalize(upRotationMat * glm::vec4(direction,0));

	// Right vector
	glm::vec3 right = glm::normalize(glm::cross(direction, up));

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		glm::vec3 new_pos = position + up * deltaTime * speed;
		if(glm::dot(glm::vec3(0,1,0), glm::normalize(new_pos))< 1.0f - epsilon){position = glm::normalize(new_pos)*glm::length(position);}
	}
	else if(glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		glm::vec3 new_pos = position - up * deltaTime * speed;
		if(glm::dot(glm::vec3(0,1,0), glm::normalize(new_pos))< 1.0f - epsilon){position = glm::normalize(new_pos)*glm::length(position);}
	}
	else if(glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS ){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								glm::vec3(0,0,0),   // and looks here : at the same position, plus "direction"
								glm::vec3(0,1,0)    // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
};

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

glm::vec3 getCameraPosition(){
	return position;
}