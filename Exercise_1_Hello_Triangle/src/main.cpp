#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Shader.h"

#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__, __LINE__);

#include<iostream>

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

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth){

    glViewport(0, 0, width, heigth);

}

void ProcessInput(GLFWwindow *window){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

}

int main(void){

    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW library!\nEnding program execution." << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    Shader shader;
    shader.ShaderParser("shaders/shader.vert");

    GLFWwindow *window = glfwCreateWindow(800, 600, "Exercise 1", NULL, NULL);

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

    float vertices[] = {
        -0.9f,  0.0f,  0.0f,
         0.0f,  0.0f,  0.0f,
        -0.45f, 0.78f, 0.0f,

         0.0f,  0.0f,  0.0f,
         0.9f,  0.0f,  0.4f,
         0.45f, 0.78f, 0.0f
    };

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int program = shader.CreateShader();

    unsigned int vao, vbo;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glGenBuffers(1, &vbo));

    GLCall(glBindVertexArray(vao));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));

    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window)){

        ProcessInput(window);

        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUseProgram(program));
        GLCall(glBindVertexArray(vao));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, 6));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
