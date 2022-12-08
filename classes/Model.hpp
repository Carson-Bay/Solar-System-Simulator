#ifndef Model_H
#define Model_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Model {
private:
    GLfloat* m_vertexBufferData;
    GLuint m_vertexBuffer;

    GLfloat* m_colorBufferData;
    GLuint m_colorBuffer;

    

public:
    Model();
    ~Model();
};
#endif
