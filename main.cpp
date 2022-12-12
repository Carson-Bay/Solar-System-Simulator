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

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 ModelMat = glm::mat4(1.0f);

    Model cube("assets/suzanne.obj");
    Shader shader( "shaders/VertexShader.glsl", "shaders/FragmentShader.glsl" );

    GLuint TextureID = loadDDS("assets/uvmap.DDS");

    shader.setVec3("LightPosition_worldspace", glm::vec3(5.0f,5.0f,5.0f));

    shader.setVec3("LightColor", glm::vec3(1.0f,1.0f,1.0f));
    shader.setFloat("LightPower", 70.0f);
    shader.setInt("texture1", 0);

    // ----- Options ----- 
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // 
    glfwSetInputMode(window, GLFW_STICKY_KEYS,GL_TRUE);
    // Background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Backface culling
    glEnable(GL_CULL_FACE);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        // Caluculate MVP
        computeMatricesFromInputs(window);
        glm::mat4 Projection = getProjectionMatrix();
        glm::mat4 View = getViewMatrix();

        glm::mat4 mvp = Projection * View * ModelMat; 

        shader.setMat("V", View);
        shader.setMat("M", ModelMat);
        shader.setMat("MVP", mvp);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        cube.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}
