#include "../include/Shader.h"
#include <GL/glfw3.h>

#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__, __LINE__);

void GLClearError()
{

    while(glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line)
{

    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL error](" << error << ") " << function <<
                  " " << file << ": " << line << std::endl;
        return false;
    }
    return true;

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

int main(void)
{

    if(!glfwInit())
    {
        std::cout << "Failed to load GLFW library!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Exercise 1", NULL, NULL);

    if(!window)
    {
        std::cout << "Failed to create window!" << std::endl;
        return -1;
    }

    float vertices[]
    {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    Shader shader;
    shader.ShaderParser("shaders/shader.vert");

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD library!" << std::endl;
        return -1;
    }

    unsigned int program = shader.CreateShader();
    unsigned int vao, vbo;
    GLCall(glGenBuffers(1, &vbo));
    GLCall(glGenVertexArrays(1, &vao));

    GLCall(glBindVertexArray(vao));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));

    GLCall(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        GLCall(glUseProgram(program));
        GLCall(glBindVertexArray(vao));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 9));

        glfwSwapBuffers(window);
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch(key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    }
}
