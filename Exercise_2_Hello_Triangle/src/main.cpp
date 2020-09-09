#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__, __LINE__);


void GLClearError(){

    while(glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line){

    while(GLenum error = glGetError()){
        std::cout << "[OpenGL error](" << error << ") " << function <<
			" " << file << ": " << line << std::endl;
        return false;
    }
    return true;

}


int main(void){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    Shader shader;
    shader.ShaderParser("shaders/shader.vert");

    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
    };

    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

//    std::cout << shaders.ShaderProgramSource.vertexSource << std::endl;
//    std::cout << shaders.ShaderProgramSource.fragmentSource << std::endl;

    GLFWwindow *window = glfwCreateWindow(800, 600, "Exercise 2", NULL, NULL);

    if(window == NULL){
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to load OpenGL library!" << std::endl;
        return -1;
    };

    unsigned int program = shader.CreateShader();

    unsigned int vao[2], vbo[2];
    GLCall(glGenVertexArrays(2, vao));
    GLCall(glGenBuffers(2, vbo));

    GLCall(glBindVertexArray(vao[0]));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), firstTriangle, GL_STATIC_DRAW));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glBindVertexArray(vao[1]));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER ,vbo[1]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), secondTriangle, GL_STATIC_DRAW));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));

    while(!glfwWindowShouldClose(window)){

        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(glUseProgram(program));
        GLCall(glBindVertexArray(vao[0]));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
        GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, 3));

        GLCall(glBindVertexArray(vao[1]));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
        GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, 3));

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(2, vao);
    glfwTerminate();
}
