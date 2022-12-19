#ifndef Mesh_H
#define Mesh_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Shader.hpp"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoordx;
    glm::vec2 TexCoordy;
    glm::vec2 TexCoordz;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
    public:
        // mesh data
        vector<Vertex>       vertices;
        vector<unsigned int> indices;
        vector<Texture>      textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
        void Draw(Shader &shader);
        void mapToSphere();
        void genSphereUVs();
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};


#endif