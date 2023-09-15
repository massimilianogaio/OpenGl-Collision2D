#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Particle.h"
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

#pragma region Shaders Variables
const char* vertexShaderPath = "src/vertex.shader";
const char* fragmentShaderPath = "src/fragment.shader";
#pragma endregion
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

       
    

    Particle p1;
    //p1.transform.setScale(vec3(1.0f));


    VertexArray va;
    VertexBuffer vb(p1.getVertices(), p1.getVerticesSize());
    IndexBuffer ib(p1.getIndices(), p1.getIndicesSize());

    VertexBufferLayout layout;
    layout.AddFloat(2);

    va.AddBuffer(vb, layout);

    Shader shader(vertexShaderPath, fragmentShaderPath);
    shader.use();


    Renderer renderer;
    glm::mat4 projectionMatrix = glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f, -1.0f, 1.0f);


    while (!glfwWindowShouldClose(window))
    {
        p1.rigidBody.update();
        std::cout << "PointsGoalReached : " << p1.transform.getPosition().x << std::endl;

        shader.SetMat4f("m_mvp", projectionMatrix);
        shader.SetMat4f("m_projection", p1.transform.getTransformMatrix());
        shader.SetUniform4f("u_Color", p1.color.x, p1.color.y, p1.color.z, p1.color.w);

        renderer.Clear();
        renderer.Draw(va, ib, shader);
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
void processInput(GLFWwindow* window);



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}