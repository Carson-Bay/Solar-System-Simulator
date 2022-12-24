#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <common/controls.hpp>
#include <common/loadTexture.hpp>
#include <classes/Model.hpp>
#include <classes/Shader.hpp>
#include <classes/Mesh.hpp>
#include <classes/Sphere.hpp>
#include <classes/GravitationalBody.hpp>
#include <classes/SolarSystem.hpp>
#include "libs/stb_image.h"

using namespace glm;

GLFWwindow* window;

#define WIDTH 1024
#define HEIGHT 768

int main(int, char**) {
    // Initialize GLFW
    glewExperimental = true;
    if(!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }
    
    // Initialize Window
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Solar System", NULL, NULL);

    if (window == NULL) {
        printf("Failed to open window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    stbi_set_flip_vertically_on_load(true);

    SolarSystem system;

    GravitationalBody body1(100.0, glm::vec3(0.0, 0.0, 0.0),glm::vec3(0.0, 0.0, 0.0));
    GravitationalBody body2(5.0, glm::vec3(5.0, 0.0, 0.0),glm::vec3(0.0, 2.0, 0.0));

    system.objects.push_back(body1);
    system.objects.push_back(body2);


    Shader shader( "shaders/VertexShader.glsl", "shaders/FragmentShader.glsl" );

    //GLuint TextureID = loadDDS("assets/uvmap.DDS");
    GLuint TextureID = loadBMP_custom("assets/SeamlessTest.bmp");

    shader.use();
    shader.setVec3("lightPos", 10.0f,10.0f,10.0f);

    shader.setVec3("lightColor", 1.0f,1.0f,1.0f);
    shader.setFloat("LightPower", 100);
    //shader.setInt("texture1", 0);

    // ----- Options ----- 
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Input
    glfwSetInputMode(window, GLFW_STICKY_KEYS,GL_TRUE);
    // Background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Backface culling
    glEnable(GL_CULL_FACE);
    // Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        // Caluculate MVP
        computeMatricesFromInputs(window);
        glm::mat4 Projection = getProjectionMatrix();
        glm::mat4 View = getViewMatrix();
        shader.setVec3("viewPos", getCameraPosition());

        shader.setMat("projection", Projection);
        shader.setMat("view", View);

        system.updateObjects();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        
        for(int i=0; i<system.objects.size();i++){
            system.objects[i].DrawObject(shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}
